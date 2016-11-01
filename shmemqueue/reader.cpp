
#include "ShmemQueue.h"
#include <iostream>

int main(int argc, char* argv[1])
{
  if (argc != 2) {
    exit(1);
  }
  ShmemQueue<int64_t> queue(atoi(argv[1]));

  int64_t ctr = 0;
  int64_t prevCtr = -1;
  while (ctr >= 0) {

    queue.read(ctr);

    if (ctr != prevCtr + 1) {
      assert("failed" == 0);
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



