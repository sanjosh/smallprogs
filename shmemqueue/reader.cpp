#include <boost/interprocess/containers/deque.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>

#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>

#include <iostream>

int main()
{
  using namespace boost::interprocess;

   //Create shared memory
   managed_shared_memory segment(open_only, "MySharedMemory");

   //Typedef the allocator
   typedef allocator<int, managed_shared_memory::segment_manager> ShmemAllocator;

   //Alias deque of ints that uses the previous allocator.
   typedef deque<uint64_t , ShmemAllocator> MyQueue;

   const ShmemAllocator allocInst(segment.get_segment_manager());

  named_mutex mutex(open_only, "fts");

   MyQueue* queue = nullptr;
   auto pair = segment.find<MyQueue>("myqueue");
   if (pair.second) {
     queue = pair.first;
   }

  int64_t ctr = 0;
  int64_t prevCtr = -1;
  while (ctr >= 0) {

    do {
      scoped_lock<named_mutex> lock(mutex);
      if (queue->size()) {
        ctr = queue->front();
        queue->pop_front();
        break;
      }
    } while (1);

    if (ctr != prevCtr + 1) {
    } else {
      prevCtr = ctr;
      if (ctr % 1000 == 0) {
        printf("read=%ld\n", ctr);
      }
    }
  }
   //typename MyQueue::const_iterator it;
   //for (it = queue->begin(); it != queue->end(); ++ it) {
     //std::cout << *it << std::endl;
   //}
}



