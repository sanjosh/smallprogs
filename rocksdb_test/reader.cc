// Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree. An additional grant
// of patent rights can be found in the PATENTS file in the same directory.
#include <cstdio>
#include <string>
#include <glog/logging.h>

#include "rocksdb/db.h"
#include "rocksdb/slice.h"
#include "rocksdb/options.h"

using namespace rocksdb;

std::string kDBPath = "/tmp/rocksdb_simple_example";

int main(int argc, char* argv[]) {

  google::InitGoogleLogging(argv[0]);

  DB* db;
  Options options;
  // Optimize RocksDB. This is the easiest way to get RocksDB to perform well
  //options.IncreaseParallelism();
  //options.OptimizeLevelStyleCompaction();
  // create the DB if it's not already present
  //options.create_if_missing = true;

  // open DB
  Status s = DB::OpenForReadOnly(options, kDBPath, &db);
  assert(s.ok());
  int round = 0;

  rocksdb::ReadOptions readOpt;
  readOpt.read_tier = kPersistedTier;

  const int64_t MAXKEYS=100*1000*1000;
  while (1) { 
    std::string value;
    for (int64_t i = 0; i < MAXKEYS; i++) {
      std::string key = "key" + std::to_string(i);
      s = db->Get(ReadOptions(), key.c_str(), &value);
      if (!s.ok()) {
        if (s.IsNotFound()) {
          LOG(INFO) << "key=" << key << " not found";
        } else {
          assert("not possible" == 0);
        }
      } else {
        if (value.find("round") == std::string::npos) {
          assert("not possible" == 0);
        }
        if (i == 1) {
          LOG(INFO) << getpid() << "got value=" << value;
        }
      }
    }
    round ++;
    LOG(INFO) << getpid() << " at round=" << round;
    delete db;
    do {
      s = DB::OpenForReadOnly(options, kDBPath, &db);
      if (!s.ok()) {
        LOG(ERROR) << "failed to open db.  err=" << s.ToString();
      }
    } while (!s.ok());
  }

  delete db;

  return 0;
}
