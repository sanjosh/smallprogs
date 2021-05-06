
/*
TODO

http://www.geeksforgeeks.org/backttracking-set-4-subset-sum/

https://www.geeksforgeeks.org/subset-sum-problem-dp-25/

https://www.geeksforgeeks.org/subset-sum-problem-osum-space/?ref=rp

http://leetcode.com/2010/09/print-all-combinations-of-number-as-sum.html
*/

#include <stdlib.h>
#include <iostream>
using namespace std;

int *Arr = NULL;

bool SubsetSum(int n, int sum)
{
    if (sum == 0)
    {
        return true;
    }
    if (n == 0) 
    {
        return false;
    }
    //cout << "entering with " << n-1 << endl;

    if (Arr[n-1] > sum)
    {
        return SubsetSum(n-1, sum);
    }

    int without = SubsetSum(n-1, sum);
    int with = SubsetSum(n-1, sum - Arr[n-1]);

    cout << "for " << Arr[n-1] << ":with=" << with << ":without=" << without << endl;

    return with || without;
}

#define N 10

int main(int argc, char* argv[])
{
    unsigned int seed;
    srand(getpid());

    Arr = new int[N];
    for (int i =0; i < N; i++)
    {
        //Arr[i] = rand_r(&seed) % N;
        Arr[i] = i;
        cout << Arr[i] << " ";
    }
    cout << endl;
    
    bool x = SubsetSum(N, N/2);
    cout << x << endl;
}
