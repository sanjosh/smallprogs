/*
 *  FM-sketch
 *  using murmurhash from https://github.com/aappleby/smhasher
 *  g++ fm_sketch.cpp -I<path>/smhasher/src <path>/smhasher/src/libSMHasherSupport.a 
 */

#include "MurmurHash3.h"

#include <stdint.h> // uint64
#include <bitset>
#include <sys/types.h> // getpid
#include <unistd.h>
#include <iostream>
#include <stdlib.h> // atoi
#include <strings.h> // bzero
#include <math.h>

uint64_t getRightmostSetBitPos(uint64_t n)
{
  return log2(n & -n) + 1;
}

static int pid = getpid();

uint32_t fm_sketch(uint32_t range)
{
  uint32_t bitmap = 0;
  for (uint32_t num = 0; num < range; num++)
  {
    uint32_t out = 0;

    MurmurHash3_x86_32((const void*)&num, sizeof(num), 
        pid, (void*)&out);

    int pos = getRightmostSetBitPos(out);
    bitmap |= (1 << (pos - 1));
    //std::cout << std::bitset<32>(bitmap) << std::endl;
  }
  return (1 << getRightmostSetBitPos(~bitmap));
}

// keep it power of 2
#define BITSHIFT 4
static const size_t NumStreams = (1 << BITSHIFT);
static const double alpha = 0.673;

/*
 * m = 2^b where b in [4,16]
 * m   : alpha 
 * 16  : 0.673
 * 32  : 0.697
 * 64  : 0.709
 * higher : 0.7213/(1 + 1.079/m)
 */

uint32_t hyperloglog64(uint32_t range)
{
  uint32_t counter[NumStreams];
  bzero(&counter, sizeof(counter));

  for (uint32_t num = 0; num < range; num++)
  {
    uint64_t out[2] = {0, 0};

    MurmurHash3_x86_128((const void*)&num, sizeof(num), 
        pid, (void*)&out);

    int idx = out[0] & (NumStreams - 1);
    out[0] = (out[0] >> BITSHIFT);

    int pos = getRightmostSetBitPos(out[0]);
    counter[idx] = (counter[idx] > pos) ? counter[idx] : pos;
  }

  // harmonic mean
  double inverse_harmonic = 0;
  for (int idx = 0; idx < NumStreams; idx ++)
  {
    uint64_t power = 1 << counter[idx];
    inverse_harmonic += (1.0f/power);
  }

  double est = (alpha * NumStreams * NumStreams)/inverse_harmonic;
  return est;
}

uint32_t hyperloglog(uint32_t range)
{
  uint32_t counter[NumStreams];
  bzero(&counter, sizeof(counter));

  for (uint32_t num = 0; num < range; num++)
  {
    uint64_t out = 0;

    MurmurHash3_x86_32((const void*)&num, sizeof(num), 
        pid, (void*)&out);

    int idx = out & (NumStreams - 1);
    out = (out >> BITSHIFT);

    int pos = getRightmostSetBitPos(out);
    counter[idx] = (counter[idx] > pos) ? counter[idx] : pos;
  }

  // harmonic mean
  double inverse_harmonic = 0;
  for (int idx = 0; idx < NumStreams; idx ++)
  {
    uint64_t power = 1 << counter[idx];
    inverse_harmonic += (1.0f/power);
  }

  double est = (alpha * NumStreams * NumStreams)/inverse_harmonic;
  return est;
}

int main(int argc, char* argv[])
{
  int start_range = 100;

  if (argc > 1) {
    start_range = atoi(argv[1]);
  }

  std::cout << "orig,fm_sketch,hyperloglog,hyperloglog64" << std::endl;
  for (int range = start_range; range < 32768; range ++) 
  {
    uint32_t num = fm_sketch(range);
    uint32_t newnum = hyperloglog(range);
    uint32_t num64 = hyperloglog64(range);
    //std::cout << std::bitset<32>(num) << std::endl;
    std::cout << range << "," << num 
      << "," << newnum 
      << "," << num64
      << std::endl;
  }
}
