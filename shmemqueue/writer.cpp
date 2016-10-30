#include <boost/interprocess/containers/deque.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/managed_shared_memory.hpp>

#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/sync/named_mutex.hpp>

#include <stdio.h>

int main()
{
  using namespace boost::interprocess;

  //Remove shared memory on construction and destruction
  struct shm_remove
  {
    shm_remove() { shared_memory_object::remove("MySharedMemory"); }
    ~shm_remove(){ shared_memory_object::remove("MySharedMemory"); }
  } sremover;

  struct mutex_remove 
  {
     mutex_remove() { named_mutex::remove("fts"); }
     ~mutex_remove(){ named_mutex::remove("fts"); }
  } mremover;

  named_mutex mutex(create_only, "fts");

  //Create shared memory
  managed_shared_memory segment(create_only, "MySharedMemory", 65536);

  //Typedef the allocator
  typedef allocator<int64_t, managed_shared_memory::segment_manager> ShmemAllocator;

  //Alias deque of ints that uses the previous allocator.
  typedef deque<int64_t , ShmemAllocator> MyQueue;

  const ShmemAllocator allocInst(segment.get_segment_manager());

  MyQueue *queue = segment.construct<MyQueue>("myqueue")(allocInst);

  int64_t ctr = 0;
  while (ctr >= 0) {
    int64_t prevCtr = ctr;
    do {
      scoped_lock<named_mutex> lock(mutex);
      if (queue->size() > 6000) {
        break;
      }
      queue->push_back(ctr);
      ctr ++;
    } while (0);

    if (prevCtr == ctr) {
      printf("sleeping=%ld\n", ctr);
    } else {
      if (ctr % 1000 == 0) {
        printf("ctr=%ld\n", ctr);
      }
    }
  }

  getchar();

  segment.destroy<MyQueue>("myqueue");
}



