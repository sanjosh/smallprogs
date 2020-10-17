

Q3. Longest palindromic substring
I first used DP but he asked me to do O(1) space complexity. I was unable to do so.

http://www.geeksforgeeks.org/longest-palindromic-substring-set-2/

Given a string, find the longest substring which is palindrome. For example, if the given string is “forgeeksskeegfor”, the output should be “geeksskeeg”.

We have discussed dynamic programming solution in the previous post. The time complexity of the Dynamic Programming based solution is O(n^2) and it requires O(n^2) extra space. We can find the longest palindrome substring in (n^2) time with O(1) extra space. The idea is to generate all even length and odd length palindromes and keep track of the longest palindrome seen so far.

Step to generate odd length palindrome:
Fix a centre and expand in both directions for longer palindromes.

Step to generate even length palindrome
Fix two centre ( low and high ) and expand in both directions for longer palindromes.
// A O(n^2) time and O(1) space program to find the longest palindromic substring
#include <stdio.h>
#include <string.h>
 
// A utility function to print a substring str[low..high]
void printSubStr(char* str, int low, int high)
{
    for( int i = low; i <= high; ++i )
        printf("%c", str[i]);
}
 
// This function prints the longest palindrome substring (LPS)
// of str[]. It also returns the length of the longest palindrome
int longestPalSubstr(char *str)
{
    int maxLength = 1;  // The result (length of LPS)
 
    int start = 0;
    int len = strlen(str);
 
    int low, high;
 
    // One by one consider every character as center point of
    // even and length palindromes
    for (int i = 1; i < len; ++i)
    {
        // Find the longest even length palindrome with center points
        // as i-1 and i. 
        low = i - 1;
        high = i;
        while (low >= 0 && high < len && str[low] == str[high])
        {
            if (high - low + 1 > maxLength)
            {
                start = low;
                maxLength = high - low + 1;
            }
            --low;
            ++high;
        }
 
        // Find the longest odd length palindrome with center
        // point as i
        low = i - 1;
        high = i + 1;
        while (low >= 0 && high < len && str[low] == str[high])
        {
            if (high - low + 1 > maxLength)
            {
                start = low;
                maxLength = high - low + 1;
            }
            --low;
            ++high;
        }
    }
 
    printf("Longest palindrome substring is: ");
    printSubStr(str, start, start + maxLength - 1);
 
    return maxLength;
}
 
// Driver program to test above functions
int main()
{
    char str[] = "forgeeksskeegfor";
    printf("\nLength is: %d\n", longestPalSubstr( str ) );
    return 0;
}

Output:

Longest palindrome substring is: geeksskeeg
Length is: 10

Time complexity: O ( n^2 ) where n is the length of input string.
Auxiliary Space: O ( 1 )

///===================================


Given a string, find the longest substring which is palindrome. For example, if the given string is “forgeeksskeegfor”, the output should be “geeksskeeg”.

Method 1 ( Brute Force )
The simple approach is to check each substring whether the substring is a palindrome or not. We can run three loops, the outer two loops pick all substrings one by one by fixing the corner characters, the inner loop checks whether the picked substring is palindrome or not.

Time complexity: O ( n^3 )
Auxiliary complexity: O ( 1 )

Method 2 ( Dynamic Programming )
The time complexity can be reduced by storing results of subproblems. The idea is similar to this post. We maintain a boolean table[n][n] that is filled in bottom up manner. The value of table[i][j] is true, if the substring is palindrome, otherwise false. To calculate table[i][j], we first check the value of table[i+1][j-1], if the value is true and str[i] is same as str[j], then we make table[i][j] true. Otherwise, the value of table[i][j] is made false.
// A dynamic programming solution for longest palindr.
// This code is adopted from following link
// http://www.leetcode.com/2011/11/longest-palindromic-substring-part-i.html
 
#include <stdio.h>
#include <string.h>
 
// A utility function to print a substring str[low..high]
void printSubStr( char* str, int low, int high )
{
    for( int i = low; i <= high; ++i )
        printf("%c", str[i]);
}
 
// This function prints the longest palindrome substring of str[].
// It also returns the length of the longest palindrome
int longestPalSubstr( char *str )
{
    int n = strlen( str ); // get length of input string
 
    // table[i][j] will be false if substring str[i..j] is not palindrome.
    // Else table[i][j] will be true
    bool table[n][n];
    memset( table, 0, sizeof( table ) );
 
    // All substrings of length 1 are palindromes
    int maxLength = 1;
    for( int i = 0; i < n; ++i )
        table[i][i] = true;
 
    // check for sub-string of length 2.
    int start = 0;
    for( int i = 0; i < n-1; ++i )
    {
        if( str[i] == str[i+1] )
        {
            table[i][i+1] = true;
            start = i;
            maxLength = 2;
        }
    }
 
    // Check for lengths greater than 2. k is length of substring
    for( int k = 3; k <= n; ++k )
    {
        // Fix the starting index
        for( int i = 0; i < n - k + 1 ; ++i )
        {
            // Get the ending index of substring from starting index i and length k
            int j = i + k - 1;
 
            // checking for sub-string from ith index to jth index iff str[i+1]
            // to str[j-1] is a palindrome
            if( table[i+1][j-1] && str[i] == str[j] )
            {
                table[i][j] = true;
 
                if( k > maxLength )
                {
                    start = i;
                    maxLength = k;
                }
            }
        }
    }
 
    printf("Longest palindrome substring is: ");
    printSubStr( str, start, start + maxLength - 1 );
 
    return maxLength; // return length of LPS
}
 
// Driver program to test above functions
int main()
{
    char str[] = "forgeeksskeegfor";
    printf("\nLength is: %d\n", longestPalSubstr( str ) );
    return 0;
}

Output:

Longest palindrome substring is: geeksskeeg
Length is: 10

Time complexity: O ( n^2 )
Auxiliary Space: O ( n^2 ) 
