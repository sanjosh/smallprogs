
http://www.codechef.com/problems/REALSET

a0 * b0 + ... + an * bn = 0
a0 * b1 + ... + an * b0 = 0
...
a0 * bn + ... + an * bn-1 = 0
===========================

This is effectively equal to poly multiplcation (A * B) = 0
IOW, F(A).F(B) = 0

S(b) [ a0 + ... + an ] = 0


[a0 ... an] [Circulant matrix] = 0

aX = b
find X

find a circulant matrix such that 

Diagonalize X
then a0.x0 = 0
    and a1.x1 = 0

