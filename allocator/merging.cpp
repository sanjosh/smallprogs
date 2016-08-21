#include <map>
#include <cstdint>
#include <cassert>
#include <iostream>

#include <random> // distrib
#include <algorithm> // random_shuffle
#include <unistd.h> // getpid

class MergingAlloc
{
  public:
  typedef uint32_t BlkId; // 4k multiple

  private:
  std::map<BlkId, size_t> freeList;
  size_t maxFreeListSize{0};

  // inverted and derived map sorted by size
  // map will have many entries for same size
  std::multimap<size_t, BlkId> sizeSortedList;

  public:

  int init(size_t numSegs)
  {
    freeList.insert(std::make_pair(0, numSegs));
    sizeSortedList.insert(std::make_pair(numSegs, 0));
    return 0;
  }

  int recover()
  {
    return 0;
  }

  int alloc(size_t numSegs, BlkId& ret_blkid)
  {
    auto iter = freeList.begin();
    static const auto iterEnd = freeList.end();
    bool found = false;

    // TODO use sizeSortedList
    auto sizeIter = sizeSortedList.lower_bound(numSegs);
    if (sizeIter != sizeSortedList.end()) {
      iter = freeList.find(sizeIter->second);
      assert(iter != iterEnd);
      found = true;
    }

    if (found)
    {
      if (iter->second > numSegs)
      {
        BlkId id = iter->first + numSegs;
        size_t sz = iter->second - numSegs;

        freeList.insert(std::make_pair(id, sz));
        sizeSortedList.insert(std::make_pair(sz, id));
      }
      ret_blkid = iter->first;
      eraseSizeSortedList(iter->second, iter->first);
      freeList.erase(iter);
      return 0;
    }
    return -1;
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

    static const auto iterEnd = freeList.end();
    decltype(freeList)::iterator prevIter = iterEnd;
    decltype(freeList)::iterator nextIter = iterEnd;

    for (auto iter = freeList.begin(); iter != iterEnd; iter ++)
    {
      if (iter->first < blkid) {
        prevIter = iter;
      } else if (iter->first > blkid) {
        nextIter = iter;
        break;
      }
    }

    //std::cout << "freeblk=" << blkid << ":" << numSegs << std::endl;

    if (prevIter != iterEnd) {

      assert (prevIter->first < insert_blkid);
      //std::cout << "  prev=" << prevIter->first << ":" << prevIter->second << std::endl;

      // check coalescing opportunity
      assert(prevIter->first + prevIter->second <= blkid);

      if (prevIter->first + prevIter->second == blkid)
      {
        // merge before
        insert_blkid = prevIter->first;
        insert_numSegs += prevIter->second;
        eraseSizeSortedList(prevIter->second, prevIter->first);
        freeList.erase(prevIter);
      }
    }

    if (nextIter != iterEnd) {

      assert (nextIter->first > insert_blkid);
      //std::cout << "  next=" << nextIter->first << ":" << nextIter->second << std::endl;

      assert(insert_blkid + insert_numSegs <= nextIter->first);

      if (insert_blkid + insert_numSegs == nextIter->first)
      {
        // merge after
        insert_numSegs += nextIter->second;
        eraseSizeSortedList(nextIter->second, nextIter->first);
        freeList.erase(nextIter);
      }
    }

    freeList.insert(std::make_pair(insert_blkid, insert_numSegs));
    sizeSortedList.insert(std::make_pair(insert_numSegs, insert_blkid));
    maxFreeListSize = std::max(maxFreeListSize, freeList.size());

    return 0;
  }

  void print(std::ostream& os)
  {
    for (auto elem : freeList)
    {
      os << "blk=" << elem.first << ":num=" << elem.second << std::endl;
    }
    for (auto elem : sizeSortedList)
    {
      os << "num=" << elem.first << ":blk=" << elem.second << std::endl;
    }
    std::cout << "max freelist size=" << maxFreeListSize << std::endl;
    // about MaxSegs / (2 * MaxAllocSize)
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

  std::vector<std::pair<MergingAlloc::BlkId, size_t>> retainList;

  std::mt19937 seedGen(getpid());
  std::uniform_int_distribution<decltype(MaxSegs)> sizeGen(1, std::min(size_t(10), MaxSegs/8));

  int ret = 0;
  while (!ret) {
    size_t reqSize = sizeGen(seedGen);
    MergingAlloc::BlkId blkid;

    ret = myalloc.alloc(reqSize, blkid);
    if (ret == 0) {
      retainList.push_back(std::make_pair(blkid, reqSize));
    }
  }

  myalloc.print(std::cout);

  std::random_shuffle(retainList.begin(), retainList.end());

  for (auto elem : retainList)
  {
    MergingAlloc::BlkId blkid;
    size_t numSegs;

    myalloc.free(elem.first, elem.second);
  }

  std::cout << "printing free list" << std::endl;
  myalloc.print(std::cout);
}
