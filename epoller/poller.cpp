#include "EPoller.h"
#include <cassert>
#include <vector>
#include <fcntl.h>

class Pipe
{
  int fd_[2];

  public:

  Pipe()
  {
    int ret = pipe2(fd_, O_NONBLOCK | O_CLOEXEC);
    assert(ret == 0);
  }

  int getReadFD() {
    return fd_[0];
  }

  int getWriteFD() {
    return fd_[1];
  }

  ~Pipe()
  {
    close(fd_[1]);
    close(fd_[0]);
  }
};

EPoller epoller;

std::atomic<uint64_t> curCount;
thread_local int readByMe = 0;

int readfunc(int fd, uint64_t ctx)
{
  Pipe* p = reinterpret_cast<Pipe*>(ctx);
  int readfd = p->getReadFD();
  assert(readfd == fd);

  do {
    uint64_t s;
    ssize_t ret = read(readfd, &s, sizeof(s));
    if (ret < 0) {
      break;
    }
    curCount ++;
    readByMe ++;
  } while (1);

  std::this_thread::yield();
}

void epollrun() {
  epoller.run();
  std::cout << "readByMe=" << readByMe << std::endl;
}

int main(int argc, char* argv[])
{
  google::InitGoogleLogging(argv[0]);

  epoller.init();

  auto p = std::unique_ptr<Pipe>(new Pipe());

  epoller.addEvent(reinterpret_cast<uint64_t>(p.get()), 
    p->getReadFD(), 
    EPOLLIN, 
    readfunc);

  std::vector<std::future<void>> futVec;

  for (int i = 0; i < 20; i++) {
    auto fut = std::async(std::launch::async,
      epollrun);
    futVec.push_back(std::move(fut));
  }

  uint64_t totalCount = 1000000;
  for (uint64_t idx = 0; idx < totalCount; idx++) {
    ssize_t ret = write(p->getWriteFD(), &idx, sizeof(idx));
    if (ret < 0) {
      totalCount --;
    }
    std::this_thread::yield();
  }

  while (curCount < totalCount) {
    usleep(100);
  }

  epoller.shutdown();

  for (auto& elem : futVec) {
    elem.wait();
  }
}

