
#include "Throttler.h"

#include <glog/logging.h>
#include <random>
#include <chrono>
#include <future>
#include <sys/time.h>

using facebook::wdt::Throttler;
using facebook::wdt::WdtOptions;
using facebook::wdt::ThreadCtx;

std::shared_ptr<Throttler> t;

double avgRatePerSec = 1024;
double peakRatePerSec = 0;
double bucketLimitBytes = 0;
int64_t throttlerLogTime_ms = 1000;
int totalThreads = 5;

void serverWorker(int index, int totalreq) {

  WdtOptions opt;
  ThreadCtx threadCtx(opt, false);

  t->registerTransfer();

  std::mt19937 seedGen(getpid() + index);
  std::uniform_int_distribution<int64_t> reqGen(avgRatePerSec/3, 2 * avgRatePerSec);

  std::ostringstream os;

  int numreq = totalreq;
  int halftime = totalreq/2;
  int one_fifth = totalreq/5;

  while (numreq > 0) {

    int64_t req = reqGen(seedGen);

    // underutilize in middle half
    if ((numreq > (halftime - one_fifth)) && (numreq < (halftime + one_fifth))) {
      usleep(100000);
      req = 1;
    }

    t->limit(threadCtx, req);

    numreq --;

    if (numreq % 50 == 0) {
      std::cerr << "thread=" << index << " reached " << numreq << std::endl;
    }
  }

  t->deRegisterTransfer();
}

int main(int argc, char* argv[])
{
  int64_t req = 100;

  if (argc > 1) {
    req = atoi(argv[1]);
  }

  t = Throttler::makeThrottler(avgRatePerSec, peakRatePerSec, bucketLimitBytes, throttlerLogTime_ms);

  std::vector<std::future<void>> futvec;
  for (int i = 0; i < totalThreads; i++) {
    auto fut = std::async(std::launch::async, serverWorker, i, req);
    futvec.push_back(std::move(fut));
  }

  for (auto& fut : futvec) {
    fut.wait();
  }

}
