#include <cstdint>
#include <cassert>
#include <string>
#include <iostream>

#include <random> // distrib
#include <algorithm> // random_shuffle
#include <unistd.h> // getpid

#include <rocksdb/db.h>
#include <rocksdb/comparator.h>

using rocksdb::Slice;
using rocksdb::DB;
using rocksdb::WriteOptions;
using rocksdb::Options;
using rocksdb::ReadOptions;

typedef uint32_t BlkId; // 4k multiple

struct IntegerComparator : public rocksdb::Comparator 
{
  virtual int Compare(const Slice& as, const Slice& bs) const override
  {
    BlkId a = *(BlkId*)as.data();
    BlkId b = *(BlkId*)bs.data();

    if (a < b) {
      return -1;
    } else if (a > b) { 
      return 1;
    } else {
      return 0;
    }
  }

  virtual const char* Name() const override
  {
    return "coalesce-int-cmp";
  }

  virtual void FindShortestSeparator(
    std::string* start,
    const Slice& limit) const override
  {
  }

  virtual void FindShortSuccessor(std::string* key) const override
  {
  }

};

class MergingAlloc
{
  public:

  private:
  DB* db;
  size_t maxFreeListSize{0};
  size_t freeListSize{0};

  // inverted and derived map sorted by size
  // map will have many entries for same size
  std::multimap<size_t, BlkId> sizeSortedList;

  std::string kDBPath = "/tmp/coalescingDB";

  public:

  int init(size_t numSegs)
  {
    kDBPath.append(std::to_string(getpid()));

    rocksdb::Options options;
    options.create_if_missing = true;
    options.error_if_exists = true;
    options.comparator = new IntegerComparator();
    auto s = DB::Open(options, kDBPath, &db);
    assert(s.ok());

    BlkId start = 0;
    Slice key((const char*)&start, sizeof(start));
    Slice value((const char*)&numSegs, sizeof(numSegs));

    db->Put(WriteOptions(), key, value);
    sizeSortedList.insert(std::make_pair(numSegs, 0));

    return 0;
  }

  int recover()
  {
    // TODO rebuild sizeSortedList from db
    return 0;
  }

  int alloc(size_t numSegs, BlkId& ret_blkid)
  {
    int retcode = -1;

    auto iter = db->NewIterator(ReadOptions());

    bool found = false;

    BlkId blkIdToUse = 0;
    size_t numSegsInBlk = 0;

    // TODO use sizeSortedList
    auto sizeIter = sizeSortedList.lower_bound(numSegs);
    if (sizeIter != sizeSortedList.end()) {

      blkIdToUse = sizeIter->second;
      numSegsInBlk = sizeIter->first;

      Slice key((const char*)&blkIdToUse, sizeof(BlkId));

      iter->Seek(key);
      assert(iter->Valid());

      found = true;
    }

    if (found)
    {
      if (numSegsInBlk > numSegs)
      {
        BlkId id = blkIdToUse + numSegs;
        size_t sz = numSegsInBlk - numSegs;

        db->Put(WriteOptions(), 
          Slice((const char*)&id, sizeof(id)), 
          Slice((const char*)&sz, sizeof(sz)));

        sizeSortedList.insert(std::make_pair(sz, id));
      }
      ret_blkid = blkIdToUse;
      eraseSizeSortedList(numSegsInBlk, ret_blkid);
      db->Delete(WriteOptions(), 
        Slice((const char*)&ret_blkid, sizeof(ret_blkid)));
      retcode = 0;
    }

    delete iter;

    return retcode;
  }

  void eraseSizeSortedList(size_t sz, BlkId blkid)
  {
    // TODO use lower bound
    auto sizeIter = sizeSortedList.find(sz);
    for (; sizeIter != sizeSortedList.end(); sizeIter ++)
    {
      if (sizeIter->second == blkid)
      {
        break;
      }
    }
    assert(sizeIter != sizeSortedList.end());
    sizeSortedList.erase(sizeIter);
  }

  /*
   * find prevIter and nextIter
   * if prev elem exists, check merge with prev
   * if next elem exists, check merge with next
   */
  int free(BlkId blkid, size_t numSegs)
  {
    assert(numSegs != 0);

    BlkId insert_blkid = blkid;
    size_t insert_numSegs = numSegs;

    std::pair<BlkId, size_t> prevTuple;
    bool prevValid = false;

    std::pair<BlkId, size_t> nextTuple;
    bool nextValid = false;

    auto iter = db->NewIterator(ReadOptions());
    iter->Seek(Slice((const char*)&blkid, sizeof(blkid)));

    if (iter->Valid())
    {
      BlkId curId = *(BlkId*)iter->key().data();
      size_t curSeg = *(size_t*)iter->value().data();

      if (curId > blkid) {
        nextTuple = std::make_pair(curId, curSeg);
        nextValid = true;
      }

      iter->Prev();

      if (iter->Valid()) {

        curId = *(BlkId*)iter->key().data();
        curSeg = *(size_t*)iter->value().data();

        if (curId < blkid) {
          prevTuple = std::make_pair(curId, curSeg);
          prevValid = true;
        }
      }
    }

    //std::cout << "new freeblk=" << blkid << ":" << numSegs << std::endl;

    if (prevValid) {

      assert (prevTuple.first < insert_blkid);
      //std::cout << "  prev=" << prevTuple.first << ":" << prevTuple.second << std::endl;

      // check coalescing opportunity
      assert(prevTuple.first + prevTuple.second <= blkid);

      if (prevTuple.first + prevTuple.second == blkid)
      {
        // merge before
        insert_blkid = prevTuple.first;
        insert_numSegs += prevTuple.second;
        eraseSizeSortedList(prevTuple.second, prevTuple.first);
        db->Delete(WriteOptions(), 
          Slice((const char*)&prevTuple.first, sizeof(prevTuple.first)));
      }
    }

    if (nextValid) {

      assert (nextTuple.first > insert_blkid);
      //std::cout << "  next=" << nextTuple.first << ":" << nextTuple.second << std::endl;

      assert(insert_blkid + insert_numSegs <= nextTuple.first);

      if (insert_blkid + insert_numSegs == nextTuple.first)
      {
        // merge after
        insert_numSegs += nextTuple.second;
        eraseSizeSortedList(nextTuple.second, nextTuple.first);
        db->Delete(WriteOptions(), 
          Slice((const char*)&nextTuple.first, sizeof(nextTuple.first)));
      }
    }

    //std::cout << "ins freeblk=" << insert_blkid << ":" << insert_numSegs << std::endl;
    db->Put(WriteOptions(), 
      Slice((const char*)&insert_blkid, sizeof(insert_blkid)), 
      Slice((const char*)&insert_numSegs, sizeof(insert_numSegs)));
    sizeSortedList.insert(std::make_pair(insert_numSegs, insert_blkid));

    //TODO use estimate num keys
    //maxFreeListSize = std::max(maxFreeListSize, freeList.size());

    return 0;
  }

  void print(std::ostream& os, int level)
  {
    os << "*****Start MergingAlloc free list" << std::endl;

    auto iter = db->NewIterator(ReadOptions());
    for (iter->SeekToFirst(); iter->Valid(); iter->Next())
    {
      if (level > 1) {
        os 
          << "blk=" << *(BlkId*)iter->key().data()
          << ":num=" << *(size_t*)iter->value().data()
          << std::endl;
      }
    }

    delete iter;

    for (auto elem : sizeSortedList)
    {
      if (level > 1) {
        os << "num=" << elem.first << ":blk=" << elem.second << std::endl;
      } 
    }
    os << "max freelist size=" << maxFreeListSize << std::endl;
    os << "*****End MergingAlloc free list" << std::endl;
    // maxFreeListSize is about MaxSegs / (2 * MaxAllocSize)
  }

};

size_t MaxSegs = 10000;

int main(int argc, char* argv[])
{
  if (argc > 1) {
    MaxSegs = atoll(argv[1]);
  }

  MergingAlloc myalloc;
  myalloc.init(MaxSegs);

  std::vector<std::pair<BlkId, size_t>> retainList;

  std::mt19937 seedGen(getpid());
  std::uniform_int_distribution<decltype(MaxSegs)> sizeGen(1, std::min(size_t(10), MaxSegs/8));

  int ret = 0;
  while (!ret) {
    size_t reqSize = sizeGen(seedGen);
    BlkId blkid;

    ret = myalloc.alloc(reqSize, blkid);
    if (ret == 0) {
      retainList.push_back(std::make_pair(blkid, reqSize));
    }
  }

  /*
  std::cout << "--retainList begin--" << std::endl;
  for (auto elem : retainList)
  {
    std::cout << "num=" << elem.first << ":blk=" << elem.second << std::endl;
  }
  std::cout << "--retainList end--" << std::endl;
  */


  myalloc.print(std::cout, 1);

  std::random_shuffle(retainList.begin(), retainList.end());

  for (auto elem : retainList)
  {
    BlkId blkid;
    size_t numSegs;

    myalloc.free(elem.first, elem.second);
  }

  myalloc.print(std::cout, 2);
}
