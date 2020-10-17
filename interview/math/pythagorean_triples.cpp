/*

given array of N elements, find 3 indices such that a[i]^2 + a[j]^2 = a[k]^2

(3,4,5)

atmost one is a square

exactly one of (a,b) is odd; c is odd
exactly one of (a,b) is divisible by 3
exactly one of (a,b) is divisible by 4
exactly one of (a,b, c) is divisible by 5

(4n+1)^2 + (4n)^2 = 4n+1

Euclid formulae 
a = 2mn; b = m^2 - n^2; c = m^2 + n^2
where one of (m,n) is odd, other is even and have no common factors

============

Dickson
find pos integers (r,s,t) : r^2 = 2st
then x=r+s; y=r+t; z=r+s+t

=============

squares of odd are always of the form 4n+1

(4n+1)^2 = 4n + 1
(4n+2)^2 = 4n 
(4n+3)^2 = 4n + 1
*/
#include <iostream>
#include <math.h>
using namespace std;

int main(int argc, char* argv[])
{
    for (int m = 2; m < 50; m+=2)
    {
        for (int n=1; n < m; n+=2)
        {
            double m2 = pow(m, 2); 
            double n2 = pow(n, 2); 
            cout << (2*m*n) << ":" << m2+n2 << ":" << m2-n2 << endl;
        }
    }
}


