
use stack of open problems  - as in max area of histogram - see karumanchi chap5,prob 24

(Karumanchi page 275 notes)
1) use XOR
1) use Hash table
1) use Dutch National flag (maintain 2 ptrs)
1) use 2 passes 
1) traverse from right or left
1) use transitivity
1) use stack or tree or hash
1) keep array of prefix sums (left and right) - and subtract
1) negation of each A[i] elem
1) addition of size to each A[i] elem
1) swapping A[i] and A[A[i]]
1) make functions over the numbers - Newton symmetric poly
1) compute hash on f([A[i])
1) Randomized algo select arbitrary elements
1) Divide Array into bins - Pigeonhole - to find duplicate elems 
1) Binary search / Fibonnaci search
1) swap using (x + y * sz)/sz = y and (x + y * sz)%sz = x

1) Inversion table uniquely determines permutation (Marshall Hall in Knuth vol 3)

=======================================
to find local maxima in array - 
    use "peak detection in time series"  - compare a[i] with a[i-1] and a[i+1]
    using wavelet
    detect zero crossings

compute sign array
    sign[i] = a[i] - a[i+1]
    2 3 4 5 3 2 1
    - - - - + + +

compute derivative
    der[i] = a[i+1] - a[i]/unit(1)
    1 1 1 -1 -1 -1 

    2nd derivative
    2der[i] 
    0 0 0 -2 0 0 
    if 2der < 0, then f has local maxima
    if 2der > 0, then f has local minima

moving average
    oldave = oldave + (newnumber - oldaverage/numexecs)
moving average is a filter
============

max XOR sum in subarray:  trie


===============

RMQ
for any computation (min, gcd, lcm) over ranges
1) precompute 2D array 
2) segment tree
3) precompute over square root decomposition
4) keep sparse table over for each [i, i + 2^j]  for all j < log(n)

--------------

http://www.geeksforgeeks.org/longest-subarray-not-k-distinct-elements/

==========

inversions

http://www.geeksforgeeks.org/count-inversions-of-size-three-in-a-give-array/

count of smaller elements to right  of each element - use BST
http://www.geeksforgeeks.org/count-smaller-elements-on-right-side/

http://www.geeksforgeeks.org/count-inversions-in-an-array-set-2-using-self-balancing-bst/

every node of Fenwick stores sum of subset of first n, where n is power of 2
parent = remove last set bit = index + (index & -index)

========

problems around smallest element in array
1. nearest on right : no intersect between consecutive nearest(i), hence use stack
2. farthest on right : there is intersect between consecutive nearest(i), hence use range array
3. count of smallest to right (inversion table) : put in tree or use merge sort
4. count of elem with at least one smaller to left and right : use stack + count

max element to right of each element - use STACK

next smaller = next greater (except change order in the stack)
Next smaller : STACK contains previous element which are greater than current

Next larger : 
1. going from left to right, STACK contains elements whose nge could be current index
2. going from right to left, STACK contains candidate nge for current index

http://www.geeksforgeeks.org/next-greater-element/
https://www.geeksforgeeks.org/next-greater-element-in-same-order-as-input/

http://www.geeksforgeeks.org/number-nges-right/

============

http://www.geeksforgeeks.org/replace-every-element-with-the-greatest-on-right-side/

https://www.geeksforgeeks.org/leaders-in-an-array/

greater than all the elements to its right side.


=============

compute over fixed length moving window 
1. drop first char in window

https://www.geeksforgeeks.org/sliding-window-maximum-maximum-of-all-subarrays-of-size-k-using-stack-in-on-time/

=============

smallest window in which all elements occur
1. detect first window
2. if start of window changes, do update 
3. keep smallest window so far

==========

SUM problems in unsorted

sum of any k = M where M is external or internal element of array
sum of any k < M where M is external or internal 

where elem is pos & negative

use
1. decrement any elem > sum/2 as elem = elem-sum/2; then find duplicates
1. hash of triplet
2. trie of triplet in sorted order
3. tree of sums of triplet

sum of pair = sum of another pair in array

===========

subarray contiguous

1. max sum (kadane)
2. max sum modulo https://www.geeksforgeeks.org/maximum-subarray-sum-modulo-m/
3. rotated array
4. if it has negative (cormen rivest)
5. rainwater trapped between two elements

https://www.geeksforgeeks.org/maximum-subarray-sum-using-divide-and-conquer-algorithm/

cormen rivest


============

distance or window problems

1. min distance between min & max element
1. max distance between same element

======

SEQUENCE

stock span problem 
1. contiguous array which is less than current element (stack)

https://www.geeksforgeeks.org/the-stock-span-problem/

----------

longest bitonic subsequence

https://www.geeksforgeeks.org/printing-longest-bitonic-subsequence/

https://www.geeksforgeeks.org/longest-bitonic-subsequence-dp-15/

-----------

Longest Increasing Subsequence (LIS)

https://www.geeksforgeeks.org/longest-common-subsequence-dp-using-memoization/

https://www.geeksforgeeks.org/longest-increasing-subsequence-dp-3/

https://www.geeksforgeeks.org/longest-monotonically-increasing-subsequence-size-n-log-n/

-----------

Max Sum subsequence with at least k distinct -

http://www.geeksforgeeks.org/maximum-sum-subsequence-least-k-distant-elements/

-----

Min jumps to end of array

snake ladder

http://www.geeksforgeeks.org/minimum-number-of-jumps-to-reach-end-of-a-given-array/

https://www.geeksforgeeks.org/minimum-number-jumps-reach-endset-2on-solution/?ref=rp

https://stackoverflow.com/questions/33227584/shortest-path-through-an-array-of-max-jump-lengths?rq=1

https://stackoverflow.com/questions/59335693/minimum-number-of-jumps-to-reach-end-of-the-array-with-sequence-using-recursion?rq=1

https://stackoverflow.com/questions/23301358/linear-time-algorithm-for-minimum-number-of-jumps-required-to-reach-end

----

modify array
https://www.geeksforgeeks.org/modify-array-to-another-given-array-by-replacing-with-the-sum-of-the-array/?ref=rp

find the element which is greater than sum of others

