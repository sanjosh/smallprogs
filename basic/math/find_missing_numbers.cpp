
/*

Missing numbers

------------------

# One missing

Approach 1 : sum 

approach 2 : XOR

Assume a1 ^ a2 ^ a3 ^ …^ an = A and a1 ^ a2 ^ a3 ^ …^ an-1 = B
Then A ^ B = an

Approach 3 : a[a[i]] = 1

------------------

# Two missing

Approach 1 sum and avg (statistical)

sum of array, avg of array - compare with sum and avg of (1..n)
one missing will be less than avg

Approach 2 XOR

XOR of all elem with (1..n)
Bit is set in result only if corresponding bits are different

https://www.geeksforgeeks.org/find-two-missing-numbers-set-2-xor-based-solution/?ref=rp
https://www.geeksforgeeks.org/find-two-missing-numbers-set-1-an-interesting-linear-time-solution/

------------------

# Four missing

indicator array

use combinatiorial design (sum of any k = find missing sum)

https://www.geeksforgeeks.org/find-four-missing-numbers-array-containing-elements-1-n/?ref=rp

compute newton sums

Muthukrishnan : data streams and algo
*/
