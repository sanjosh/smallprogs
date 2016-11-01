#include "ShmemQueue.h"
#include <stdio.h>

int main()
{
  ShmemQueue<int64_t> queue(8000, getpid());

  int64_t ctr = 0;
  while (ctr >= 0) {
    int64_t prevCtr = ctr;
    do {
      queue.write(ctr);
      ctr ++;
    } while (0);

    if (prevCtr == ctr) {
      printf("sleeping=%ld\n", ctr);
    } else {
      if (ctr % 1000 == 0) {
        printf("ctr=%ld\n", ctr);
        getchar();
      }
    }
  }

  getchar();
}



