// Copyright (c) 2013, Facebook, Inc.  All rights reserved.
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree. An additional grant
// of patent rights can be found in the PATENTS file in the same directory.
//
#include <cstdio>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <string>

#include "rate_limiter.h"

#include <chrono>
#include <future>
#include <random>

#include <sys/time.h>

using namespace rocksdb;

typedef std::chrono::high_resolution_clock Clock;

std::unique_ptr<RateLimiter> limiter;

int64_t rate_bytes_per_sec = 1024; // 1 MB per sec
int64_t refill_period_us = 1000000;
int32_t fairness = 5;
int32_t totalThreads = 5;

int64_t start_time = 0;

int64_t getmytime()
{
   struct timeval tp;
   gettimeofday(&tp, NULL);
   long long mslong = (long long) tp.tv_sec * 1000L + tp.tv_usec / 1000; //get current timestamp in milliseconds
   return mslong;
}

void serverWorker(int index, int totalreq) {

  std::mt19937 seedGen(getpid() + index);
  std::uniform_int_distribution<int64_t> reqGen(rate_bytes_per_sec/3, rate_bytes_per_sec);

  rocksdb::GenericRateLimiter* limiter_ptr = dynamic_cast<rocksdb::GenericRateLimiter*>(limiter.get());

  std::ostringstream os;

  int numreq = totalreq;
  int halftime = totalreq/2;
  int one_tenth = totalreq/10;

  rocksdb::Env::IOPriority pri = (index < totalThreads/2) ? Env::IO_LOW : Env::IO_HIGH;
  //rocksdb::Env::IOPriority pri = Env::IO_HIGH;

  while (numreq > 0) {

    int64_t req = reqGen(seedGen);

    // underutilize in middle half
    if ((numreq > (halftime - one_tenth)) && (numreq < (halftime + one_tenth))) {
      req = 1;
    }

    limiter_ptr->Request(req, pri);

    if (pri == Env::IO_LOW) {
      os << req << ",0," << limiter_ptr->available_bytes_ << "," << getmytime() - start_time << std::endl;
    } else {
      os << "0," << req << "," << limiter_ptr->available_bytes_ << "," << getmytime() - start_time << std::endl;
    }

    numreq --;
    if (numreq % 50 == 0) {
      std::cerr << "thread=" << index << " reached " << numreq << std::endl;
    }
  }
  std::cout << os.str();
}

int main(int argc, char* argv[]) {

  int64_t req = 100;

  if (argc > 1) { 
    req = atoi(argv[1]);
  }

  std::cout << "required,available,time_us" << std::endl;

  limiter = std::unique_ptr<rocksdb::RateLimiter>(new rocksdb::GenericRateLimiter(
        rate_bytes_per_sec,
        refill_period_us,
        fairness));

  start_time = getmytime();

  std::vector<std::future<void>> futvec;
  for (int i = 0; i < totalThreads; i++) {
    auto fut = std::async(std::launch::async, serverWorker, i, req);
    futvec.push_back(std::move(fut));
  }

  for (auto& fut : futvec) {
    fut.wait();
  }

}
