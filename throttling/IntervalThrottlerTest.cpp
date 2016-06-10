
#include "IntervalThrottler.h"
#include <unistd.h>

int main(int argc, char* argv[])
{
  int times = 100;
  if (argc > 1) 
  {
    times = atoi(argv[1]);
  }

  IntervalThrottler t;

  t.setDesiredInterval(1);

  for (int i = 0; i < times; i++)
  {
    t.limit();
    //usleep(1000000 - 100000);
    usleep(200);
  }
}
