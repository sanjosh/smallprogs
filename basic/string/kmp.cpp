
/**

pattern index 

LPS (longest prefix which is also suffix of 0..i

lps[idx] = N

implies pat[0..N-1] = pat[idx - N - 1, idx]

search from left to right

if pattern match fails at index=j, then shift pattern index to right by lps[j-1]

 */


#include <iostream>
using namespace std;
#include <bits/stdc++.h>

/**
 test cases for pattern
incr prefix : ab - abc - abcd
decr prefix : abcd - abc - ab
same  : aaaaaa
diff : abcdef
*/

// Fills lps[] for given patttern pat[0..M-1]
void computeLPSArray(char* pat, int M, int* lps)
{
    // length of the previous longest prefix suffix
    int prefix_len_matched = 0;

    lps[0] = 0; // lps[0] is always 0

    cout << pat << endl;

    // the loop calculates lps[i] for i = 1 to M-1
    int i = 1;
    while (i < M) {
        ///cout << "current=" << prefix_len_matched << "," << pat[i] << ":" << pat[prefix_len_matched] << endl;
        if (pat[i] == pat[prefix_len_matched]) {
            prefix_len_matched++;
            lps[i] = prefix_len_matched;
            //cout << i << ":m=" << prefix_len_matched << endl;
            i++;
        }
        else // (pat[i] != pat[prefix])
        {
            // you hit 'd' in 'abcabcd' - reset search
            if (prefix_len_matched != 0) {
                //cout << "len[" << prefix_len_matched -1 << "]=" << lps[prefix_len_matched - 1] << endl;
                prefix_len_matched = lps[prefix_len_matched - 1];
                assert(prefix_len_matched == 0);
                // when would this entry be non-zero ?
            }
            else 
            {
                // found mismatch of 'd' with 'a' during ababd
                lps[i] = 0;
                i++;
            }
        }
    }
}

// Prints occurrences of txt[] in pat[]
void KMPSearch(char* pat, char* txt)
{
    int M = strlen(pat);
    int N = strlen(txt);

    // create lps[] that will hold the longest prefix suffix
    // values for pattern
    int lps[M];

    // Preprocess the pattern (calculate lps[] array)
    computeLPSArray(pat, M, lps);

    int i = 0; // index for txt[]
    int j = 0; // index for pat[]
    while (i < N) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }

        if (j == M) {
            printf("Found pattern at index %d ", i - j);
            j = lps[j - 1];
        }

        // mismatch after j matches
        else if (i < N && pat[j] != txt[i]) {
            if (j != 0)  { 
                // partial match ? 
                // skip pattern forward by last successful prefix matched
                // lps[] = { 0, 0, 1, 2, 0}
                // mismatch in txt="abab[a]bgh" with pat="abab[d]"
                // when mismatch at i=4, j = 4
                // j = lps[4-1 = 3] = 2
                // go back in pattern to j=2 instead of j=0
                // pattern match resumes looking at "abab[a]abgh" with "ab[a]bd"
                // with i=4, j=2
                cout << " at " << i << " pat index reset=" << j << " to " << lps[j-1] << endl;
                j = lps[j - 1]; 
            }
            else {
                cout << "moving on " << i << endl;
                i = i + 1; // no match; look at next char
            }
        }
    }
}


int main()
{
    char txt[] = "abababgh";
    char pat[] = "ababd";
    int lps[strlen(pat)];
    computeLPSArray(pat, strlen(pat), lps);
    for (int i = 0; i < strlen(pat); i ++)
    {
        cout << lps[i] << ",";
    }
    cout << endl;
    KMPSearch(pat, txt);
    return 0;
}
