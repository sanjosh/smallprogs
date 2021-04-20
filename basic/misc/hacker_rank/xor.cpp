
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

// hackerran - max xor sum

unsigned int brute(unsigned int l, unsigned int r) 
{
    unsigned int max = 0;
    unsigned int a= 0;
    unsigned int b= 0;
    for (int i = l; i < r; i++)
    {
        for (int j = i; j <= r; j++)
        {
            unsigned int myxor= (i ^ j);
            if (myxor > max) {max = myxor ; a= i; b=j ;}
        }
    }
    printf("Brute %u %u:%u %u \n", l, r, a, b);
    return max;
}


unsigned int maxXorLow(unsigned int l, unsigned int r) 
{
    unsigned max = 0;
    unsigned int a = l;
    unsigned int b = r;

    for (int i = 9; i >= 0; i--)
    {
        max = 1 << i;
        if (!(l & max)) // bit not set
        {
            if ((b | max) <= r) 
            { 
                b |= max;
                ////printf("xoring %u bit %u\n", i, b);
            }
        }
        else
        {
            if ((b & ~max) >= l) 
            { 
                b &= (~max);
                //printf("anding %u bit %u\n", i, b);
            }
        }
    }
    
    //printf("low %u %u:%u %u:%u\n", l, r, a, b, a^b);

    assert( a >= l);
    assert( a <= r);

    assert( b >= l);
    assert( b <= r);

    assert( a <= b);

    return (a ^ b);
}

// working
unsigned int maxXorHigh(unsigned int l, unsigned int r) 
{
    unsigned max = 0;
    unsigned int a = l;
    unsigned int b = r;

    for (int i = 9; i >= 0; i--)
    {
        max = 1 << i;
        if (!(r & max)) // r does not have bit
        {
            if ((a | max) < r) 
            { 
                a |= max; // try it in a
                //printf("xoring %u bit %u\n", i, a);
            }
        }
        else
        {
            if ((a & ~max) > l)  // r has bit set
            { 
                a &= (~max); // unset it in a
                //printf("anding %u bit %u\n", i, a);
            }
        }
    }
    
    //printf("high %u %u:%u %u:%u\n", l, r, a, b, a^b);

    assert( a >= l);
    assert( a <= r);

    assert( b >= l);
    assert( b <= r);

    assert( a <= b);

    return (a ^ b);
}

#define MAX(a,b) ( a > b) ? a : b 

bool isPower(unsigned int a)
{
    unsigned int x = 1;
    unsigned int count = 0;
    while (x)
    {
        if (a & x) count ++;
        x = x << 1;
    }
    return (count == 1);
}

int main(int argc, char* argv[]) {
    unsigned int res;
    unsigned int _l;
    unsigned int _r;

    if (argc == 3)
    {
        _l = atoi(argv[1]);
        _r = atoi(argv[2]);
    }
    else
    {
        scanf("%u", &_l);
        scanf("%u", &_r);
    }
    
    unsigned int high = maxXorHigh(_l, _r);
    unsigned int low = maxXorLow(_l, _r);
    res = MAX(high, low);
    //res = brute(_l, _r);
    assert(isPower(res + 1));
    //printf("RES for %u:%u IS %u\n", _l, _r, res);
    printf("%u\n", res);
    
    return 0;
}
