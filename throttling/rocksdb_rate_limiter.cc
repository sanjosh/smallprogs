// Copyright (c) 2013, Facebook, Inc.  All rights reserved.
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree. An additional grant
// of patent rights can be found in the PATENTS file in the same directory.
#include <cstdio>
#include <iostream>
#include <unistd.h>
#include <string>

#include "util/rate_limiter.h"

#include <chrono>

using namespace rocksdb;

typedef std::chrono::high_resolution_clock Clock;

int main(int argc, char* argv[]) {

  int64_t rate_byter_per_sec = 1024;
  int64_t refill_period_us = 1000000;
  int32_t fairness = 10;

  int req = 1;

  if (argc > 1) { 
    req = atoi(argv[1]);
  }

  std::unique_ptr<RateLimiter> limiter(new rocksdb::GenericRateLimiter(
        rate_byter_per_sec,
        refill_period_us,
        fairness));

  limiter->Request(rate_byter_per_sec, Env::IO_HIGH);

  // unused time
  usleep(refill_period_us * 5);

  while (req > 0) {
    Clock::time_point begin;
    begin = Clock::now();

    limiter->Request(rate_byter_per_sec, Env::IO_HIGH);

    Clock::time_point end;
    end = Clock::now();
    int64_t interval = std::chrono::duration_cast<std::chrono::microseconds>(
      end - begin).count();

    std::cout << "sleep for " << interval << std::endl;
    req --;
  }
}
