// https://www.geeksforgeeks.org/range-minimum-query-for-static-array/

// C++ program to do range minimum
// query in O(1) time with
// O(n Log n) extra space and
// O(n Log n) preprocessing time
#include <bits/stdc++.h>
using namespace std;
#define MAX 500

// lookup[i][j] is going to
// store index of minimum value in
// arr[i..j]. Ideally lookup
// table size should not be fixed
// and should be determined using
// n Log n. It is kept
// constant to keep code simple.
int lookup[MAX][MAX];

// Structure to represent a query range
struct Query {
    int L, R;
};

// Fills lookup array
// lookup[][] in bottom up manner.
void preprocess(int arr[], int n)
{
    // Initialize M for the
    // intervals with length 1
    for (int i = 0; i < n; i++)
        lookup[i][0] = i;

    // Compute values from smaller to bigger intervals
    for (int range = 1; (1 << range) <= n; range++)
    {
        // Compute minimum value for all intervals with size 2^j
        for (int start = 0; (start + (1 << range) - 1) < n; i++)
        {
            int prev_range = range - 1;
            int offset = 1 << (range-1);
            // take the min of previous two sub-ranges
            lookup[start][range] = std::min(arr[lookup[start][prev_range]], arr[lookup[start + offset][prev_range]]);
        }
    }
}

// Returns minimum of arr[L..R]
int query(int arr[], int L, int R)
{
    // For [2,10], j = 3
    int j = (int)log2(R - L + 1);

    int next_offset = R - (1 << j) + 1;

    // For query [2,10], we take min of two intersecting ranges, each of length 8
    // one range from (0, 8) and another range from (2, 10)
    return std::min(arr[lookup[L][j]], arr[lookup[next_offset][j]])
}

// Prints minimum of given
// m query ranges in arr[0..n-1]
void RMQ(int arr[], int n, Query q[], int m)
{
    // Fills table lookup[n][Log n]
    preprocess(arr, n);

    // One by one compute sum of all queries
    for (int i = 0; i < m; i++)
    {
        // Left and right boundaries
        // of current range
        int L = q[i].L, R = q[i].R;

        // Print sum of current query range
        cout << "Minimum of [" << L << ", "
             << R << "] is "
             << query(arr, L, R) << endl;
    }
}

// Driver code
int main()
{
    int a[] = { 7, 2, 3, 0, 5, 10, 3, 12, 18 };
    int n = sizeof(a) / sizeof(a[0]);
    Query q[] = { { 0, 4 }, { 4, 7 }, { 7, 8 } };
    int m = sizeof(q) / sizeof(q[0]);
    RMQ(a, n, q, m);
    return 0;
}
