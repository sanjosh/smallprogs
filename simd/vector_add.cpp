/* 
 * g++ -msse2 -std=c++11 
 */

#include <x86intrin.h>
#include <iostream>

// int is base type
// aatribute specifies size of vector in bytes
// 16-byte vector divides into 4 ints
typedef int v4si __attribute__ ((vector_size (16)));

// m128d is 128-bit vector of 2 doubles
__m128d in1_create(double min, double max)
{
  return (__m128d){min, max};
}
    
int main()
{
  v4si a{0, 0, 0, 0}; 
  v4si b{1, 2, 3, 4}; 
  v4si c{20, 19, 18, 17};

  long l;
    
  // addition of vectors
  a = b + c; 

  for (int i = 0; i < 4; i++)
  {
    std::cout
      << a[i] << ","
      << b[i] << ","
      << c[i] << std::endl;
  }

  auto x = in1_create(0.5, 3.5);

  std::cout << x[0] << "," << x[1] << std::endl;
}

