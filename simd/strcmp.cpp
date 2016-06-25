#include <nmmintrin.h>
#include <stdio.h>

/**
 * g++ -msse4 <prog>
 * https://gcc.gnu.org/bugzilla/show_bug.cgi?id=53712
 */

int substr( const char* s1, const char * s2 )
{
        __m128i s1chars = _mm_loadu_si128( (const __m128i *) s2 );
        __m128i s2chars = _mm_loadu_si128( (const __m128i *) (s1));
        return _mm_cmpistri( s1chars, s2chars, _SIDD_CMP_EQUAL_ANY );
}

int exact( const char* s1, const char * s2 )
{
        __m128i s1chars = _mm_loadu_si128( (const __m128i *) s2 );
        __m128i s2chars = _mm_loadu_si128( (const __m128i *) (s1));
        return _mm_cmpistri( s1chars, s2chars, _SIDD_CMP_EQUAL_EACH );
}

int main( int argc, char * argv[] )
{
        const char* s1 = "1234567890b1234567890";
        const char* s2 = "abcdefghijklmnop";
        const char* s3 = "13579";

        int r = substr( s1, s2 );
        fprintf( stderr, "Result: %d\n", r );

        r = substr( s1, s3);
        fprintf( stderr, "Result: %d\n", r );

        r = exact( s3, s3);
        fprintf( stderr, "Result: %d\n", r );

        r = exact( s1, s2);
        fprintf( stderr, "Result: %d\n", r );

        return 0;
}
