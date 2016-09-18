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
#include <future>
#include <random>

using namespace rocksdb;

typedef std::chrono::high_resolution_clock Clock;

std::unique_ptr<RateLimiter> limiter;

int64_t rate_bytes_per_sec = 1024 * 1024; // 1 MB per sec
int64_t refill_period_us = 1000000;
int32_t fairness = 100;
int32_t totalThreads = 5;

void serverWorker(int index, int numreq) {

  std::mt19937 seedGen(getpid() + index);
  std::uniform_int_distribution<int64_t> reqGen(1, rate_bytes_per_sec/totalThreads);

  while (numreq > 0) {

    int64_t req = reqGen(seedGen);

    limiter->Request(req, Env::IO_HIGH);

    Clock::time_point end;
    end = Clock::now();

    std::time_t ttp = std::chrono::system_clock::to_time_t(end);

    std::cout << index << "," << req << "," << std::ctime(&ttp);

    numreq --;
  }
}

int main(int argc, char* argv[]) {

  int64_t req = 1024;

  if (argc > 1) { 
    req = atoi(argv[1]);
  }

  limiter = std::unique_ptr<rocksdb::RateLimiter>(new rocksdb::GenericRateLimiter(
        rate_bytes_per_sec,
        refill_period_us,
        fairness));

  std::vector<std::future<void>> futvec;
  for (int i = 0; i < totalThreads; i++) {
    auto fut = std::async(std::launch::async, serverWorker, i, req);
    futvec.push_back(std::move(fut));
  }

  for (auto& fut : futvec) {
    fut.wait();
  }

}
