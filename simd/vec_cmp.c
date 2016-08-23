/* gcc -msse2 */

#include <emmintrin.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
  char keys[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h',
    'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p' };
  const int count = sizeof(keys)/sizeof(keys[0]);

  char c = 'b';
  if (argc > 1) {
    c = argv[1][0];
  }

  // compare c aginst all stored keys
  __m128i cmp16 = _mm_cmpeq_epi8(_mm_set1_epi8(c),
      _mm_loadu_si128((__m128i *)keys));

  const int bitmap16 = _mm_movemask_epi8(cmp16) & (( 1 << count) - 1);

  if (bitmap16) {
    printf("found %d\n", __builtin_ctz(bitmap16));
  } else {
    printf("not found\n");
  }
}
