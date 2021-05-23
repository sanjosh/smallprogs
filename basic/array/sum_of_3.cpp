
 When the integers are in the range [-u, \dots, u], 3SUM can be solved in O(n + u\log u) time 
 by representing the input set S as a bit vector, computing the set S+S of all pairwise 
 sums as a discrete convolution using the Fast Fourier transform, and finally comparing this set to -S.

From WIkipedia
=====================

find 3 elem in array whose sum is K

If K is odd - 1/3 or 3/3 has to be odd
if K is even - 1/3 or 3/3 is even)

sep input into even & odd using Dutch national flag problem

sort odd  - nlogn
sort even - nlogn

if K is odd
    for each odd in ascending order until (K<odd)
        search for (K-odd) in even space
        search for (K-odd) in odd space
if K is even
    for each even in ascending order until (K<even)
        search for (K-even) in odd space
        search for (K-even) in even space
