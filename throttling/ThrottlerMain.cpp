/*
 * add_executable(throttler
 *   ThrottlerMain.cpp
 *   )
 *
 * target_link_libraries(throttler wdt_min)
 *
 */

#include "Throttler.h"

using facebook::wdt::Throttler;
using facebook::wdt::WdtOptions;
using facebook::wdt::ThreadCtx;

int main(int argc, char* argv[])
{
  double avgRatePerSec = 1024;
  double peakRatePerSec = 4096;
  double bucketLimitBytes = 1024;
  int64_t throttlerLogTime_ms = 100;

  auto t = Throttler::makeThrottler(avgRatePerSec, peakRatePerSec, bucketLimitBytes, throttlerLogTime_ms);

  WdtOptions opt;
  ThreadCtx threadCtx(opt, false);

  t->registerTransfer();

  for (int i = 0; i < 1000; i++)
  {
    t->limit(threadCtx, 100 * ((i+1)%10));
  }

  t->deRegisterTransfer();
}
