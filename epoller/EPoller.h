#include <sys/epoll.h> // epoll
#include <glog/logging.h> // LOG
#include <list> 
#include <functional> // std::function
#include <mutex> // unique_lock
#include <future>  // std::async
#include <memory>  // unique_ptr
#include <atomic>  // atomic
#include <cassert>  

#include "EventFD.h"  // EventFD

/**
 * abstraction around epoll event loop
 */
class EPoller {

  static constexpr int MAX_EVENTS_PER_POLL = 20;

  int fd_ = -1; // on which epoll_wait done
  int maxEventsPerPoll_ = MAX_EVENTS_PER_POLL;

  // need an EventFD to wake thread from epoll
  std::unique_ptr<EventFD> shutdownPtr_;

  // set at start of shutdown to prevent more threads
  bool mustExit_ = false;

  std::atomic<uint32_t> numThreads_{ 0 };
  std::condition_variable exitCondition_;
  std::mutex exitMutex_;

  typedef std::function<int(int, uint64_t)> EventHandler;

  static constexpr int MAGIC = 0xDEAFBABE;

  struct EPollCtx {
    const EventHandler handler_;
    const uint64_t userData_;
    const int fd_;
    const int magic_ = MAGIC;
  };

  typedef std::unique_ptr<EPollCtx> EPollCtxPtr;

  std::mutex eventListMutex_;
  std::list<EPollCtxPtr> eventList_;

  // TODO
  // timers
  // stats
  // getter 
  public:

  int init() {

    int ret = -1;

    do {

      fd_ = epoll_create1(EPOLL_CLOEXEC);
      if (fd_ < 0) {
        LOG(ERROR) << "epollfd create failed" << errno;
        close(fd_);
        fd_ = -1;
        ret = -errno;
        break;
      }
  
      try {
        shutdownPtr_ = std::unique_ptr<EventFD>(new EventFD());
      } catch (const std::exception& e) {
        LOG(ERROR) << "failed to create shutdown notifier " << e.what();
        close(fd_);
        fd_ = -1;
        break;
      }

      const uint64_t shutdownKey = reinterpret_cast<uint64_t>(shutdownPtr_.get());

      ret = addEvent(shutdownKey, shutdownPtr_->getfd(), EPOLLIN, 
          std::bind(&EventFD::readfd, shutdownPtr_.get(), std::placeholders::_1));
      if (ret < 0) {
        close(fd_);
        fd_ = -1;
        dropEvent(shutdownKey, shutdownPtr_->getfd());
        break;
      }

      ret = 0;

    } while (0);

    if (ret == 0) {
      LOG(INFO) << "started epoller=" << (void*)this;
    }

    return ret;
  }

  int shutdown() {

    if (shutdownPtr_) {

      {
        mustExit_ = true;
        // no thread can enter epoller::run now
        // but what if a thread exits on its own accord before shutdown notification?
        // then the thread calling shutdown() could get stuck waiting 
        // to prevent that, this thread waits with a timeout
        while (numThreads_) {

          LOG(INFO) << "num threads remaining=" << numThreads_;
          shutdownPtr_->writefd();

          std::unique_lock<std::mutex> l(exitMutex_);
          exitCondition_.wait_for(l, std::chrono::microseconds(10));
        }
      }
      // reset ptr AFTER thread has exited
      shutdownPtr_.reset();
      LOG(INFO) << "shutting down epoller=" << (void*)this;
    }
    return 0;
  }

  ~EPoller() {

    shutdown();

    {
      std::unique_lock<std::mutex> l(eventListMutex_);
      eventList_.clear();
    }

    if (fd_ != -1) {
      close(fd_);
      fd_ = -1;
    }
  }

  int getFD() const {
    return fd_;
  }

  /**
   * Create hierarchy of epoll fds
   * add fd of this EPoller to epoll_wait() of another EPoller
   */
  int addToAnotherEPoller(EPoller& other) {

    auto handler = std::bind(&EPoller::eventHandler, this, 
        std::placeholders::_1,
        std::placeholders::_2);

    return other.addEvent(reinterpret_cast<uint64_t>(this),
      getFD(),
      EPOLLIN | EPOLLOUT,
      std::move(handler));
  }

  /**
   * called from processEvent of another EPoller
   * @param fd
   * @param userData
   */
  int eventHandler(int fd, uint64_t userData) {
    assert(fd == fd_);
    assert(userData == (uint64_t)this);
    run(1);
	return 0;
  }

  /**
   * @param key
   */
  int processEvent(uint64_t key) {

    int handlerRet = 0;

    EPollCtx* ctx = (EPollCtx*)key;
    if (ctx->magic_ != MAGIC) {
      LOG(ERROR) << "received unknown event with ptr=" << ctx;
      handlerRet = -ENOENT;
    } else {
      handlerRet = ctx->handler_(ctx->fd_, ctx->userData_);
    }
    return handlerRet;
  }

  /**
   * can be called by any thread which wants to process 
   * events on this EPoller fd
   */
  int run(int32_t numLoops = -1) {

    {
      if (mustExit_) {
        LOG(WARNING) << "epoller is exiting..";
        return 0;
      } else {
        numThreads_ ++;
      }
    }
    
    while ((false == mustExit_) && (numLoops != 0)) {

      epoll_event readyEvents[maxEventsPerPoll_];
      bzero(readyEvents, sizeof(epoll_event) * maxEventsPerPoll_);

      int numEvents = 0;

      do {
        numEvents = epoll_wait(fd_, readyEvents, maxEventsPerPoll_, -1);
      } while ((numEvents < 0) && (errno == EINTR || errno == EAGAIN));

      if (numEvents < 0) {
        LOG(ERROR) << "epoll_wait=" << (void*)this << " got errno=" << errno;
        continue;
      } else if (numEvents > 0) {
        for (int i = 0; i < numEvents; i++) {
          epoll_event &thisEvent = readyEvents[i];
          int handlerRet = processEvent(thisEvent.data.u64);
		  (void)handlerRet;
        }
      }
      
      if (numLoops > 0) {
        numLoops --;
      }
    }

    if (mustExit_) {
      std::unique_lock<std::mutex> l(exitMutex_);
      std::notify_all_at_thread_exit(exitCondition_, std::move(l));
    }
    numThreads_ --;
	return 0;
  }

 
  /**
   * @param userData which will passed as arg to eventHandler
   * @param eventFD which is added to epoll_wait
   * @param readWrite can be EPOLLIN | EPOLLOUT
   * @param eventHandler function which is called on eventFD getting an event
   * @return 0 on success, negative errno on error
   */

  int addEvent(uint64_t userData, 
    int eventFD, 
    int readWrite, 
    EventHandler eventHandler) {

    // validate input
    if (eventFD < 0) {
      LOG(ERROR) << "eventFD=" << eventFD << " is invalid";
      return -EINVAL;
    }

    auto ctxptr = EPollCtxPtr(new EPollCtx{eventHandler, userData, eventFD});

    epoll_event eventInfo;
    bzero(&eventInfo, sizeof(eventInfo));

    eventInfo.events = readWrite | EPOLLET;
    eventInfo.data.u64 = reinterpret_cast<uint64_t>(ctxptr.get());

    int ret = epoll_ctl(fd_, EPOLL_CTL_ADD, eventFD, &eventInfo);
    if (ret < 0) {
      LOG(ERROR) << "Failed to add event.  errno=" << errno;
      ret = -errno;
    } else {
      std::unique_lock<std::mutex> l(eventListMutex_);
      eventList_.push_back(std::move(ctxptr));
    }

    return ret;
  }

  /**
   * @param userData which was used in addEvent
   * @param eventFD which was used in addEvent
   * @return 0 on success, negative errno on error
   */
  int dropEvent(uint64_t userData, int eventFD) {

    int delRet = epoll_ctl(fd_, EPOLL_CTL_DEL, eventFD, nullptr);

    if (delRet < 0) {
      LOG(ERROR) << "unable to delete existing event for fd=" << eventFD 
        << " userData=" << userData
        << " from epoll fd=" << fd_
        << " errno=" << errno;
      delRet = -errno;
    }

    bool found = false;
    {
      std::unique_lock<std::mutex> l(eventListMutex_);
      for (auto iter = eventList_.cbegin(); 
          iter != eventList_.cend();
          iter ++) {

        EPollCtx* c = iter->get();
        if ((c->userData_ == userData) && (c->fd_ == eventFD)) {
          found = true;
          eventList_.erase(iter);
          break;
        }
      }
    }

    if (false == found) {
      LOG(ERROR) << "unable to delete event for fd=" << eventFD 
        << " userData=" << userData
        << " from eventList of size=" << eventList_.size();
      delRet = -ENOENT;
    }

    return delRet;
  }

  int addTimer()
  {
    return 0;
  }

  int dropTimer()
  {
    return 0;
  }
};
