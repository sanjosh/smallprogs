/*

http://www.careercup.com/question?id=6287528252407808

TODO

A k-palindrome is a string which transforms into a palindrome on removing at most k characters.

Given a string S, and an interger K, print "YES" if S is a k-palindrome; otherwise print "NO".
Constraints:
S has at most 20,000 characters.
0<=k<=30

Sample Test Case#1:
Input - abxa 1
Output - YES
Sample Test Case#2:
Input - abdxa 1
Output - No
*/

#include <iostream>
#include <string>
#include <string.h>
#include <assert.h>
using namespace std;

#define max(a,b) (a > b ? a : b)
#define min(a,b) (a < b ? a : b)

#define MAX 40

int dp[MAX][MAX];

int ModifiedEditDistance(const string& a, const string& b, int k) 
{
    int n = a.size();
    // for simplicity. we should use only a window of size 2*k+1 or 
    // dp[2][MAX] and alternate rows. only need row i-1
    memset(dp, 0x3f, sizeof (dp));    // init dp matrix to a value > 1.000.000.000
    for (int i = 0 ; i < n; i++)
    {
        dp[i][0] = dp[0][i] = i;
    }

    assert(n < MAX);

    for (int i = 1; i <= n; i++) 
    {
        int from = max(1, i-k); 
        int to = min(i+k, n);

        for (int j = from; j <= to; j++) 
        {
            if (a[i-1] == b[j-1])           // same character
                dp[i][j] = dp[i-1][j-1];    
            // note that we don't allow letter substitutions
            
            dp[i][j] = min(dp[i][j], 1 + dp[i][j-1]); // delete character j
            dp[i][j] = min(dp[i][j], 1 + dp[i-1][j]); // insert character i
            
            cout << "(" << i << "," << j << ")=" << dp[i][j] << " ";
        }
        cout << endl;
    }
    return dp[n][n];
}


int main(int argc, char* argv[])
{
    cout << ModifiedEditDistance("abxa", "axba", 1) << endl;  // 2 <= 2*1 - YES
    cout << ModifiedEditDistance("abdxa", "axdba", 1) << endl; // 4 > 2*1 - NO
    cout << ModifiedEditDistance("abaxbabax", "xababxaba", 2) << endl; // 4 <= 2*2 - YE
}
