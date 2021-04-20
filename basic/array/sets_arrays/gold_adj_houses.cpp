
// Given a lane where there are various houses each containing a fixed amount of gold. Now a robber has to rob the houses such that when he robs a house the adjacent one cannot be robbed.Calculate the maximum amount of gold collected by him.(Classic Dp question).
//
//
#include <iostream>
#include <stdlib.h>

using namespace std;
#define MAX(a, b) (a>b ? a : b)

int sumAll(int totalSum[], int a[], int i, int n)
{
    if (i == n-1) {
        return (totalSum[i] = a[i]);
    }
    else {
        int with = totalSum[i];
        if (with == -1) {
            with = a[i] + (i + 2 < n ? sumAll(totalSum, a, i + 2, n) : 0);
        }                    
        int without = totalSum[i + 1];
        if (without == -1) {
            without = (i + 1 < n) ? sumAll(totalSum, a, i + 1, n) : 0;
        }                
        return std::max(with, without);
    }
}

int main(int argc, char* argv[])
{
#define N 10
    int a[N];
    int totalSum[N];
    unsigned int seed = getpid();
    srand(seed);
    for (int i = 0; i < N; i++)
    {
        totalSum[i] = -1;
        a[i] = rand_r(&seed) % N;
        cout << a[i] << " ";
    }
    cout << endl;

    int x = sumAll(totalSum, a, 0, N);

    cout << "max is " << x << endl;

    for (int i = 0; i < N; i++)
    {
        cout << totalSum[i] << " ";
    }
    cout << endl;
}

