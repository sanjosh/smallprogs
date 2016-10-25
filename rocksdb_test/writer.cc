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

  google::InitGoogleLogging("writer_example");

  DB* db;
  Options options;
  // Optimize RocksDB. This is the easiest way to get RocksDB to perform well
  options.IncreaseParallelism();
  options.OptimizeLevelStyleCompaction();
  // create the DB if it's not already present
  options.create_if_missing = true;

  auto s = rocksdb::DestroyDB(kDBPath, options);
  assert(s.ok());

  // open DB
  s = DB::Open(options, kDBPath, &db);
  assert(s.ok());

  int round = 0;
  LOG(INFO) << "db created";

  const int64_t MAXKEYS=1000*1000*1000;
  while (1) {
    // insert lots of keys
    for (int64_t i = 0; i < MAXKEYS; i++) {
      std::string key = "key" + std::to_string(i);
      // indicates round in which was updated
      std::string value = "round" + std::to_string(round);
      value.append(4096, 'a');
      s = db->Put(WriteOptions(), key.c_str(), value);
      assert(s.ok());
      if ((round != 0) && i && (i % 100000 == 0)) {
        db->SyncWAL();
        LOG(INFO) << "sync wal key=" << i;
      }
    }
    if (round == 0) {
      db->SyncWAL();
    }
    round ++;
    LOG(INFO) << "round=" << round;
    google::FlushLogFiles(0);
  }

  delete db;

  return 0;
}
