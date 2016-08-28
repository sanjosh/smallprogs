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
#include <math.h>

uint32_t getRightmostSetBitPos(uint32_t n)
{
  return log2(n & -n) + 1;
}

int main(int argc, char* argv[])
{
  int pid = getpid();
  int range = 100;

  if (argc > 1) {
    range = atoi(argv[1]);
  }

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

  uint32_t invert_bitmap = ~bitmap;
  int pos = getRightmostSetBitPos(invert_bitmap);
  double final = (double(1 << pos))/0.77351f;

  std::cout 
    << std::bitset<32>(bitmap)
    << ":" << std::bitset<32>(invert_bitmap)
    << ":pos=" << pos
    << ":estimate of N=" << final
    << std::endl;
}
