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

  public:

  int init(size_t numSegs)
  {
    freeList.insert(std::make_pair(0, numSegs));
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
    for (; iter != iterEnd; iter ++)
    {
      if (iter->second >= numSegs)
      {
        found = true;
        break;
      }
    }

    if (found)
    {
      if (iter->second > numSegs)
      {
        freeList.insert(std::make_pair(
          iter->first + numSegs,
          iter->second - numSegs));
      }
      ret_blkid = iter->first;
      freeList.erase(iter);
      return 0;
    }
    return -1;
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
        freeList.erase(nextIter);
      }
    }

    freeList.insert(std::make_pair(insert_blkid, insert_numSegs));
    maxFreeListSize = std::max(maxFreeListSize, freeList.size());

    return 0;
  }

  void print(std::ostream& os)
  {
    for (auto elem : freeList)
    {
      os << "blk=" << elem.first << ":num=" << elem.second << std::endl;
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
