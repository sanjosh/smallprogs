#include <stdio.h>

/* Boyer-Moore : 

For each P[i]
    BUild RightMost[P[i]] array

Given text T and pattern P
 if T[k] letter mismatched with P[i] letter
   shift pattern P along by max[1, i - RightMost(T[k])] 

suffix ternary tree better than trie and BST

*/
 

char * strstr(char* string, char* substring)
{
    register char *a, *b;

    /* First scan quickly through the two strings looking for a
     * single-character match.  When it's found, then compare the
     * rest of the substring.
     */

    b = substring;
    if (*b == 0) 
    {
        return string;
    }
    for ( ; *string != 0; string += 1) 
    {
        if (*string != *b) 
        {
            continue;
        }
        a = string;
        while (1) 
        {
            if (*b == 0) 
            {
                return string;
            }
            if (*a++ != *b++) 
            {
                break;
            }
        }
        b = substring;
    }
    return (char *) 0;
}

int main(int argc, char* argv[])
{
    char* pos = strstr(argv[1], argv[2]);
    printf("%s\n", pos);
}

/* Program for Bad Character Heuristic of Boyer Moore String Matching Algorithm */
 
# include <limits.h>
# include <string.h>
# include <stdio.h>
 
# define NO_OF_CHARS 256
 
// A utility function to get maximum of two integers
int max (int a, int b) { return (a > b)? a: b; }
 
// The preprocessing function for Boyer Moore's bad character heuristic
void badCharHeuristic( char *str, int size, int badchar[NO_OF_CHARS])
{
    int i;
 
    // Initialize all occurrences as -1
    for (i = 0; i < NO_OF_CHARS; i++)
         badchar[i] = -1;
 
    // Fill the actual value of last occurrence of a character
    for (i = 0; i < size; i++)
         badchar[(int) str[i]] = i; // rightmost occurence of char
}
 
/* A pattern searching function that uses Bad Character Heuristic of
   Boyer Moore Algorithm */
void search( char *txt,  char *pat)
{
    int m = strlen(pat);
    int n = strlen(txt);
 
    int badchar[NO_OF_CHARS];
 
    /* Fill the bad character array by calling the preprocessing
       function badCharHeuristic() for given pattern */
    badCharHeuristic(pat, m, badchar);
 
    int s = 0;  // s is shift of the pattern with respect to text
    while(s <= (n - m))
    {
        int j = m-1;
 
        /* Keep reducing index j of pattern while characters of
           pattern and text are matching at this shift s */
        while(j >= 0 && pat[j] == txt[s+j])
            j--;
 
        /* If the pattern is present at current shift, then index j
           will become -1 after the above loop */
        if (j < 0)
        {
            printf("\n pattern occurs at shift = %d", s);
 
            /* Shift the pattern so that the next character in text
               aligns with the last occurrence of it in pattern.
               The condition s+m < n is necessary for the case when
               pattern occurs at the end of text */
            s += (s+m < n)? m-badchar[txt[s+m]] : 1;
 
        }
 
        else
            /* Shift the pattern so that the bad character in text
               aligns with the last occurrence of it in pattern. The
               max function is used to make sure that we get a positive
               shift. We may get a negative shift if the last occurrence
               of bad character in pattern is on the right side of the
               current character. */
            s += max(1, j - badchar[txt[s+j]]);
    }
}
