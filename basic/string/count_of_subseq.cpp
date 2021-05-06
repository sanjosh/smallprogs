

/**

number of times one string occurs in another as a subsequence

 */
#include <iostream>
#include <string>

using namespace std;

int count_subseq(string& text, string& pattern, int t, int p) {

    if (p == pattern.size()) return 1;
    if (t == text.size()) return 0;

    if (text[t] == pattern[p]) {
        return count_subseq(text, pattern, t + 1, p + 1) + count_subseq(text, pattern, t + 1, p);
    }
    else {
        return count_subseq(text, pattern, t + 1, p);
    }
}

int count_subseq2(string a, string b)
{
    int m = a.length();
    int n = b.length();

    // Create a table to store results of sub-problems
    int lookup[m + 1][n + 1] = { { 0 } };

    // If first string is empty
    for (int i = 0; i <= n; ++i)
        lookup[0][i] = 0;

    // If second string is empty
    for (int i = 0; i <= m; ++i)
        lookup[i][0] = 1;

    // Fill lookup[][] in bottom up manner
    for (int i = 1; i <= m; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            // If last characters are same, we have two
            // options -
            // 1. consider last characters of both strings
            //    in solution
            // 2. ignore last character of first string
            if (a[i - 1] == b[j - 1])
                lookup[i][j] = lookup[i - 1][j - 1] +
                               lookup[i - 1][j];

            else
                // If last character are different, ignore
                // last character of first string
                lookup[i][j] = lookup[i - 1][j];
        }
    }

    cout << endl;
    for (int i = 0; i <= m; i++)
    {
        for (int j = 0; j <= n; j++)
        {
            cout << lookup[i][j] << ",";
        }
        cout << endl;
    }

    return lookup[m][n];
}

int main()
{
    string text = "geegee";
    string pattern = "gee";

    cout << count_subseq(text, pattern, 0, 0) << endl;
    cout << count_subseq2(text, pattern) << endl;
}
