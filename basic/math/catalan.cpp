
/*
http://www.geeksforgeeks.org/program-nth-catalan-number/

C0=1
CN+1 = Sum (i=0,n) Ci.Cn-i
c1 = c0 = 1
c2 = c0.c1 + c1.c0 = 2
c3 = c0.c2 + c1.c1 + c2.c0 = 2.c0.c2 + c1.c1 = 2.c0.c2 + c1.c1
        = 4.c0^2.c1 + c1.c1
c4 = c0.c3 + c1.c2 + c2.c1 + c3.c0
c5 = c0.c4 + c1.c3 + c2.c2 + c3.c1 + c4.c0

closed form
Cn = 1/(n+1) * Binomial(2n/n)
    = Product (over k=2,n) (n+k/k) (i.e. n+2/2 . n+3/3 . n+4/4..n+n/n)

*/

#include <iostream>
#include <stdlib.h>
#include <assert.h>

using namespace std;

int memo[100];

int catalan(int n)
{
    cout << "called for " << n << endl;

    if (memo[n] != -1) 
    {
        cout << "return " << memo[n] << " for " << n << endl;
        return memo[n];
    }

    int res = 0;
    for (int i = 0; i <= n-1; i++)
    {
        res += catalan(i)*catalan(n-1-i);
    }
    memo[n] = res;
    cout << "set " << res << " for " << n << endl;
    return res;
}

int main(int argc, char* argv[])
{
    for (int i=0 ; i < 100; i++)
    {
        memo[i] = -1;
    }
    memo[0] = memo[1] = 1;
    int n = atoi(argv[1]);
    assert(n < 100);

    int x= catalan(n);
    cout << x << endl;
}

