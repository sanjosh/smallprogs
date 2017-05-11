// g++ -std=c++11 -mrtm <file>
#include <immintrin.h>
#include <iostream>

int main()
{
  unsigned status;
  if ((status = _xbegin()) == _XBEGIN_STARTED) {
    _xend();
  } else {
    _xabort(_XABORT_CONFLICT);
  }
}
