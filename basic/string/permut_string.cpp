
http://www.geeksforgeeks.org/write-a-c-program-to-print-all-permutations-of-a-given-string/

TODO

Gray code - Knuth Vol 2

n-bit Gray Codes can be generated from list of (n-1)-bit Gray codes using following steps.
1) Let the list of (n-1)-bit Gray codes be L1. Create another list L2 which is reverse of L1.
2) Modify the list L1 by prefixing a ’0′ in all codes of L1.
3) Modify the list L2 by prefixing a ’1′ in all codes of L2.
4) Concatenate L1 and L2. The concatenated list is required list of n-bit Gray codes.


=================
Lexicographic order
# include <stdio.h>
 
/* Function to swap values at two pointers */
void swap (char *x, char *y)
{
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
  
/* Function to print permutations of string
   This function takes three parameters:
   1. String
   2. Starting index of the string
   3. Ending index of the string. */
void permute(char *a, int i, int n)
{
   int j;
   if (i == n)
     printf("%s\n", a);
   else
   {
        for (j = i; j <= n; j++)
       {
          swap((a+i), (a+j));
          permute(a, i+1, n);
          swap((a+i), (a+j)); //backtrack
       }
   }
}
 
/* Driver program to test above functions */
int main()
{
   char a[] = "ABC"; 
   permute(a, 0, 2);
   getchar();
   return 0
}
