
/*
Powerset problem
http://stackoverflow.com/questions/9648661/given-a-set-s-find-all-the-maximal-subsets-whose-sum-k

1. Get the size of power set
    powet_set_size = pow(2, set_size)
2  Loop for counter from 0 to pow_set_size
     (a) Loop for i = 0 to set_size
          (i) If ith bit in counter is set
               Print ith element from set for this subset



Power Set

Power Set Power set P(S) of a set S is the set of all subsets of S. For example S = {a, b, c} then P(s) = {{}, {a}, {b}, {c}, {a,b}, {a, c}, {b, c}, {a, b, c}}.

If S has n elements in it then P(s) will have 2^n elements


Algorithm:

Input: Set[], set_size
1. Get the size of power set
    powet_set_size = pow(2, set_size)
2  Loop for counter from 0 to pow_set_size
     (a) Loop for i = 0 to set_size
          (i) If ith bit in counter is set
               Print ith element from set for this subset
     (b) Print seperator for subsets i.e., newline

Example:

Set  = [a,b,c]
power_set_size = pow(2, 3) = 8
Run for binary counter = 000 to 111

Value of Counter            Subset
    000                    -> Empty set
    001                    -> a
    011                    -> ab
   100                     -> c
   101                     -> ac
   110                     -> bc
   111                     -> abc

Program:
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 
void printPowerSet(char *set, int set_size)
{
    /*set_size of power set of a set with set_size
      n is (2**n -1)*/
    unsigned int pow_set_size = pow(2, set_size);
    int counter, j;
 
    /*Run from counter 000..0 to 111..1*/
    for(counter = 0; counter < pow_set_size; counter++)
    {
        for(j = 0; j < set_size; j++)
        {
          /* Check if jth bit in the counter is set
             If set then print jth element from set */
            if(counter & (1<<j))
                printf("%c", set[j]);
        }
        printf("\n");
    }
}
 
/*Driver program to test printPowerSet*/
int main(int argc, char* argv[])
{
    int n = 3;
    if (argc > 1) n = atoi(argv[1]);
    char* set = new char[n];
    for (int i = 0; i < n; i++)
    {
        set[i] = 'a' + i;
    }
    printPowerSet(set, n);
 
    getchar();
    return 0;
}
