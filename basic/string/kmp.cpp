
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
        cout << "current=" << prefix_len_matched << "," << pat[i] << ":" << pat[prefix_len_matched] << endl;
        if (pat[i] == pat[prefix_len_matched]) {
            prefix_len_matched++;
            lps[i] = prefix_len_matched;
            cout << i << ":m=" << prefix_len_matched << endl;
            i++;
        }
        else // (pat[i] != pat[len])
        {
            // This is tricky. Consider the example.
            // AAACAAAA and i = 7. The idea is similar
            // to search step.
            if (prefix_len_matched != 0) {
                cout << "len[" << prefix_len_matched -1 << "]=" << lps[prefix_len_matched - 1] << endl;
                prefix_len_matched = lps[prefix_len_matched - 1];
                // Also, note that we do not increment
                // i here
            }
            else // if (len == 0)
            {
                lps[i] = 0;
                cout << i << ":n=" << 0 << endl;
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
            // Do not match lps[0..lps[j-1]] characters,
            // they will match anyway
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
}

// Driver program to test above function
int main()
{
    char txt[] = "ABABDABACDABABCABAB";
    char pat[] = "ABABCABAB";
    int lps[strlen(pat)];
    KMPSearch(pat, txt);
    return 0;
}
