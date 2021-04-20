#include <string.h>
#include <stdio.h>

// palindrome

// NEED A permutation-indep transform - Newton symmetric poly
// Compute hash(x1.x2.x3...) = x1^2 + x2^2 + ... xn^2 

// anothre approach - reve string and find all common seq between the 2

int main(int argc, char* argv[])
{
    char* str = argv[1];
    int start = 0;
    int len = strlen(str);

    int maxLen = 1;
    int low;
    int high;

    for (int i = 1; i < len; i++)
    {   
        low = i-1;
        high = i;

        // for even
        while ((low >= 0) && (high < len) && (str[low] == str[high]))
        {
            if (high - low + 1 > maxLen)
            {
                start = low;
                maxLen = high - low + 1;
            }
            --low;
            ++high;
        }

        // TODO for odd
    }
    
    printf("longest=%s %d %d", str, start, maxLen);
}

