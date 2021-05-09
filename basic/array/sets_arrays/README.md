
use stack of open problems  - as in max area of histogram - see karumanchi chap5,prob 24

## Solution

1. keep prefix sums over each range (0, i) where i = 1..N
1. keep min over each range (i, N) where i = 1..N

(Karumanchi page 275 notes)

1. use XOR
1. use Hash table
1. use Dutch National flag (maintain 2 ptrs)
1. use 2 passes 
1. traverse from right or left
1. use transitivity
1. use stack or tree or hash
1. keep array of prefix sums (left and right) - and subtract
1. negation of each A[i] elem
1. addition of size to each A[i] elem
1. swapping A[i] and A[A[i]]
1. make functions over the numbers - Newton symmetric poly
1. compute hash on f([A[i])
1. Randomized algo select arbitrary elements
1. Divide Array into bins - Pigeonhole - to find duplicate elems 
1. Binary search / Fibonnaci search
1. swap using (x + y * sz)/sz = y and (x + y * sz)%sz = x



1) Inversion table uniquely determines permutation (Marshall Hall in Knuth vol 3)


## misc

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


## max XOR sum in subarray:  

trie


## RMQ

for any computation (min, gcd, lcm) over ranges
1. precompute 2D array 
2. segment tree
3. precompute over square root decomposition
4. keep sparse table over for each [i, i + 2^j]  for all j < log(n)

http://www.geeksforgeeks.org/longest-subarray-not-k-distinct-elements/

## inversions

http://www.geeksforgeeks.org/count-inversions-of-size-three-in-a-give-array/

count of smaller elements to right  of each element - use BST
http://www.geeksforgeeks.org/count-smaller-elements-on-right-side/

http://www.geeksforgeeks.org/count-inversions-in-an-array-set-2-using-self-balancing-bst/

every node of Fenwick stores sum of subset of first n, where n is power of 2
parent = remove last set bit = index + (index & -index)

## problems around smallest or largest element in array

1. next smallest on right : nested relation between consecutive nearest(i), hence use stack
2. farthest smallest on right : there is no nesting between consecutive nearest(i), hence you need suffix min array
3. count of smallest to right (inversion table) : put in tree or use merge sort
4. count of elem with at least one smaller to left and right : use stack + count

### smallest or largest on left or right

max element to right of each element - use STACK

next smaller same as next greater (except change order in the stack)

next smaller : STACK contains previous element which are greater than current

Next smaller or larger can be done in two ways : 
1. going from left to right, STACK contains elements whose nge could be current index
2. going from right to left, STACK contains candidate nge for current index

http://www.geeksforgeeks.org/next-greater-element/

traverse from right to left to get sorted 
https://www.geeksforgeeks.org/next-greater-element-in-same-order-as-input/

### farthest smaller on right 

distance based, not absolute.   therefore, cannot keep min or max array 

auxiliary structure needed

https://www.geeksforgeeks.org/find-the-farthest-smaller-number-in-the-right-side

keep suffix min array where suffixmin[i] = min (i.. N-1)

suffixmin is sorted such that suffixmin[i] <= suffixmin[i+1]

then do binary search on this array

### max rainwater trapped between two elements

keep absolute max on left or right

https://www.geeksforgeeks.org/trapping-rain-water/

### next smaller after next greater

https://www.geeksforgeeks.org/find-next-smaller-next-greater-array/

run next greater and next smaller

### Number of greater

http://www.geeksforgeeks.org/number-nges-right/

### replace with greatest

http://www.geeksforgeeks.org/replace-every-element-with-the-greatest-on-right-side/

https://www.geeksforgeeks.org/leaders-in-an-array/

greater than all the elements to its right side.

## compute over fixed length moving window 

1. drop first char in window

https://www.geeksforgeeks.org/sliding-window-maximum-maximum-of-all-subarrays-of-size-k-using-stack-in-on-time/

## smallest window in which all elements occur

1. detect first window
2. if start of window changes, do update 
3. keep smallest window so far

## SUM problems in unsorted

sum of any k = M where M is external or internal element of array
sum of any k < M where M is external or internal 

where elem is pos & negative

use
1. decrement any elem > sum/2 as elem = elem-sum/2; then find duplicates
1. hash of triplet
2. trie of triplet in sorted order
3. tree of sums of triplet

sum of pair = sum of another pair in array

## subarray contiguous

### max sum (kadane)

currentSum = max(currentSum + x, 0)

maxSum = max(maxSum, sum)

https://www.geeksforgeeks.org/maximum-subarray-sum-using-divide-and-conquer-algorithm/

### max sum modulo 

maximize the sum by decrementing some sum before

you have to find largest prefix sum before, decrementing which will cause current prefix sum to increase

keep prefix sums (0, i) for all i=1, N

for each new prefix (0, j) 
   find largest prefix computed before which is greater than or equal to this (prefix + 1)
   (NOTE : if you find equal to prefix, it will cancel due to modulo)
   this is the subtractor which will give max modulo
   compute (this prefix - that prefix + M) 
   this is sum of [i, j] mod M
   this can be greater than current max sum

https://www.geeksforgeeks.org/maximum-subarray-sum-modulo-m/

### max sum in rotated array

find start via binary search

## distance or window problems

1. min distance between min & max element
1. max distance between same element

## stock span problem 

find contiguous array to left which is less than current element (stack)

find next greater element on left

stack contains indices of elements (smallest on top)

https://www.geeksforgeeks.org/the-stock-span-problem/

## longest bitonic subsequence

https://www.geeksforgeeks.org/printing-longest-bitonic-subsequence/

https://www.geeksforgeeks.org/longest-bitonic-subsequence-dp-15/

## Longest Increasing Subsequence (LIS)

https://www.geeksforgeeks.org/longest-common-subsequence-dp-using-memoization/

https://www.geeksforgeeks.org/longest-increasing-subsequence-dp-3/

https://www.geeksforgeeks.org/longest-monotonically-increasing-subsequence-size-n-log-n/

## Max Sum subsequence with at least k distinct -

http://www.geeksforgeeks.org/maximum-sum-subsequence-least-k-distant-elements/

## Min jumps to end of array

snake ladder (BFS on graph)

http://www.geeksforgeeks.org/minimum-number-of-jumps-to-reach-end-of-a-given-array/

https://www.geeksforgeeks.org/minimum-number-jumps-reach-endset-2on-solution/?ref=rp

https://stackoverflow.com/questions/33227584/shortest-path-through-an-array-of-max-jump-lengths?rq=1

https://stackoverflow.com/questions/59335693/minimum-number-of-jumps-to-reach-end-of-the-array-with-sequence-using-recursion?rq=1

https://stackoverflow.com/questions/23301358/linear-time-algorithm-for-minimum-number-of-jumps-required-to-reach-end

## modify array

https://www.geeksforgeeks.org/modify-array-to-another-given-array-by-replacing-with-the-sum-of-the-array/?ref=rp

find the element which is greater than sum of others

