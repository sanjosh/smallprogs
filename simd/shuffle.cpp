/* 
 * g++ -mavx2 -std=c++11 
 * https://software.intel.com/en-us/forums/intel-c-compiler/topic/309988
 */

// sse header files are in /usr/lib/<compiler> dir
#include <x86intrin.h>
#include <iostream>

int main()
{
  int32_t input[] = {9, 10, 11, 12};

  __m128i a = _mm_loadu_si128((__m128i*)input);

  // shuffle 32-bit values in 128-bit vector
  __m128i res = _mm_shuffle_epi32(a, _MM_SHUFFLE(3, 1, 2, 0));

  // sizeof(a) * 8 = number of bits = 128
  std::cout << sizeof(a) << std::endl;

  for (int idx = 0; idx < 4; idx++)
  {
    std::cout
      << a[idx] << "->"
      << res[idx] << std::endl;
  }
}

