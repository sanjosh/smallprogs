#include <iostream>
#include <iomanip>
#include <stdlib.h>

// bits.stephan-brumme.com/minmax.html

int minima(int a, int b)
{
   int diff = a - b;
   std::cout << std::hex << (a ^ b) << std::dec << std::endl;
   // bit31 is 0xFFFFFFFF is a<b, else 0
   int bit31 = (diff >> 31);
   // applying xor twice eliminates the number
   // a xor b xor b = a
   return (bit31 & (a ^ b)) ^ b;
}

int main(int argc, char* argv[])
{
  int a = atoi(argv[1]);
  int b = atoi(argv[2]);
  std::cout << minima(a, b) << std::endl;
}
