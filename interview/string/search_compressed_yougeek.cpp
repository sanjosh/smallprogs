
#include <stdio.h>
#include <ctype.h>
#include <assert.h>

// http://yougeeks.blogspot.in/2014/08/directi-interview-question-given.html

 
 
void function(const char *s , int position)
{
    int i=0; 
    int currentLength=0;                                    // cl=> current length
    int prevLength;                                           // pl=> previous length

    //printf("called pos=%d\n", position);

    while(currentLength < position)
    {
        prevLength=currentLength;
        if (isalpha(s[i]))                            // condition to check whether it is number or any alphabate
        {
            ++i;
            ++currentLength;
        }
        else
        {
            currentLength = currentLength*(s[i]-'0');                      // multiply the current length by the number found
            ++i;
        }
    }
 
    if (currentLength > position)                                  // if current length is greater than the position
    {                                              // it simply means that that string till pl is repeated by the number found
        int tmp = position % prevLength;                         // so simply search in that prefix :)
        if(!tmp)                                    // for perfect match
            tmp=prevLength;

        function(s,tmp);                            // Reducing the search domain
    }
    else 
    {
        assert(currentLength == position);

        if (isalpha(s[i-1]))         // if current length is equals to the position and there was no
        {                                  // number at the last of the prefix : print answer
            printf("%c ",s[i-1]);
        }
        else // if current length is equals to the position and there was a number
        {                                               // at the last simply print the character before the number :)
            printf("%c ",s[i-2]);
        }
    }
}
 
// abc3z2pq3
int main(int argc, char** argv)
{
    for (size_t i = 1; i <= 66; i++)
    {
        function("abc3z2pq3", i);
    }
    printf("\n");
    return 0;
}// eo main
