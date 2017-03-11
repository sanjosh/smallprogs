#pragma once

#include <boost/interprocess/containers/deque.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>

#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/sync/named_condition.hpp>

#include <memory>

namespace bip = boost::interprocess;

template <class D>
class ShmemQueue
{
  typedef bip::allocator<D, bip::managed_shared_memory::segment_manager> ShmemAlloc;
  typedef bip::deque<D, ShmemAlloc> BaseQueue;

  bool isCreator_{false};

  const std::string name_;
  const std::string mutexName_;
  const std::string condName_;
  bip::named_mutex mutex_;
  bip::named_condition cond_;
  bip::managed_shared_memory segment_;
  ShmemAlloc allocator_;
  BaseQueue* queue_{nullptr};

  public:

  ShmemQueue(int pid, size_t numEntries)
    : isCreator_(true)
    , name_("n" + std::to_string(pid))
    , mutexName_(name_ + "m")
    , condName_(name_ + "c")
    , mutex_(bip::create_only, mutexName_.c_str())
    , cond_(bip::create_only, condName_.c_str())
    , segment_(bip::create_only, name_.c_str(), numEntries * sizeof(D))
    , allocator_(segment_.get_segment_manager())
  {
    // TODO call shared_memory_object::remove(name_);
    // before creating segment_ ?
    // same for mutex_ and cond_ ?
    queue_ = segment_.construct<BaseQueue>(name_.c_str())(allocator_);
  }


  ShmemQueue(int pid)
    : isCreator_(false)
    , name_("n" + std::to_string(pid))
    , mutexName_(name_ + "m")
    , condName_(name_ + "c")
    , mutex_(bip::open_only, mutexName_.c_str())
    , cond_(bip::open_only, condName_.c_str())
    , segment_(bip::open_only, name_.c_str())
    , allocator_(segment_.get_segment_manager())
  {
    auto pair = segment_.find<BaseQueue>(name_.c_str());
    if (pair.second) {
      queue_ = pair.first;
    } else {
      throw std::runtime_error("could not find queue=" + name_);
    }
  }

  ~ShmemQueue() {
    delete queue_;
    if (isCreator_) {
      segment_.destroy<BaseQueue>(name_.c_str());
      bip::shared_memory_object::remove(name_.c_str());
      bip::named_mutex::remove(mutexName_.c_str());
      bip::named_condition::remove(condName_.c_str());
    }
  }

  int write(const D& d) {
    bip::scoped_lock<decltype(mutex_)> lock(mutex_);
    queue_->push_back(d);
    cond_.notify_one();
    return 0;
  }

  int try_read(D& d) {
    bip::scoped_lock<decltype(mutex_)> lock(mutex_);
    if (not queue_->size()) {
      return -1;
    }
    d = queue_->front();
    queue_->pop_front();
    return 0;
  }

  int read(D& d) {
    bip::scoped_lock<decltype(mutex_)> lock(mutex_);
    while (not queue_->size()) {
      cond_.wait(lock);
    }
    d = queue_->front();
    queue_->pop_front();
    return 0;
  }
};

typedef std::unique_ptr<ShmemQueue> ShmemQueueUPtr;
typedef std::shared_ptr<ShmemQueue> ShmemQueueSPtr;
