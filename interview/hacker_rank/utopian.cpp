#include <stdlib.h>
#include <stdio.h>

// hackerrank

int RealPow(int a)
{
    int i = 1;

    int b = a;
    while (b--)
    {
        i = (i << 1);
    }
    return i;
}

int GetLowBits(int a)
{
    return RealPow(a) - 1;
}

int main(int argc, char* argv[])
{
    int numInputs = 0;
    int res = scanf("%d", &numInputs);

    if (res <= 0)
    {
        exit(1);
    }

    int *testInput = new int[numInputs];
    for (int i = 0; i < numInputs; i++)
    {
        res = scanf("%d", &testInput[i]);
        if (res <= 0)
        {
            exit(1);
        }
    }
    
    int t[] = {1, 2};
    for (int i = 0; i < numInputs; i++)
    {
        int res = 0;

        int& n = testInput[i];

        if (n < 2)
        {
            res = t[n];
        }
        // odd = evaluate using closed form formula
        // T_odd(n) = (2^(n/2) * T[1]) + ((2^(n/2) - 1) * 2)
        else if (n & 0x01)
        {
            int mod = (n/2);
            res = (RealPow(mod) * t[1]) + ((GetLowBits(mod)) * 2);
        }
        // even
        else
        {
            int mod = ((n-1)/2);
            // just add 1 to odd case 
            res = (RealPow(mod) * t[1]) + ((GetLowBits(mod)) * 2) + 1;
        }
        printf("%u\n", res);
    }
    delete []testInput;
}
