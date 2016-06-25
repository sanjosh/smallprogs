
/*
 * g++ -mss2
 * https://software.intel.com/en-us/forums/intel-isa-extensions/topic/501607
 */

#include <x86intrin.h>
#include <iostream>


int main(int argc, char* argv[])
{
  float A[] = {3.0f, 13.0f, 33.0f, 43.0f};
  float B[] = {4.0f, 14.0f, 34.0f, 44.0f};
  float C[] = {5.0f, 15.0f, 35.0f, 45.0f};
  float D[] = {6.0f, 16.0f, 36.0f, 46.0f};

  __m128 a[4],tmp[4];

  a[0] = _mm_loadu_ps(A);
  a[1] = _mm_loadu_ps(B);
  a[2] = _mm_loadu_ps(C);
  a[3] = _mm_loadu_ps(D);

  tmp[0] = _mm_unpacklo_ps(a[0], a[1]);
  tmp[2] = _mm_unpacklo_ps(a[2], a[3]);
  tmp[1] = _mm_unpackhi_ps(a[0], a[1]);
  tmp[3] = _mm_unpackhi_ps(a[2], a[3]);

  a[0] = _mm_shuffle_ps(tmp[0], tmp[2], _MM_SHUFFLE(1,0,1,0) );
  a[1] = _mm_shuffle_ps(tmp[0], tmp[2], _MM_SHUFFLE(3,2,3,2) );
  a[2] = _mm_shuffle_ps(tmp[1], tmp[3], _MM_SHUFFLE(1,0,1,0) );
  a[3] = _mm_shuffle_ps(tmp[1], tmp[3], _MM_SHUFFLE(3,2,3,2) );

  _mm_storeu_ps(A, a[0]);
  _mm_storeu_ps(B, a[1]);
  _mm_storeu_ps(C, a[2]);
  _mm_storeu_ps(D, a[3]);

  for (int i = 0; i < 4; i ++)
  {
    std::cout 
      << A[i] << ","
      << B[i] << ","
      << C[i] << ","
      << D[i] 
      << std::endl;
  }
}
