
COMMON TECHNIQUES

https://www.geeksforgeeks.org/window-sliding-technique/

https://www.geeksforgeeks.org/tag/sliding-window/

https://www.geeksforgeeks.org/prefix-sum-array-implementation-applications-competitive-programming/

https://www.geeksforgeeks.org/sqrt-square-root-decomposition-technique-set-1-introduction/


array subset 
- square root decomposition 
- binary decomposition
- fenwick tree

------------
greedy

dynamic prog - find recursion - all choices have to be explored 
- explore tree usng program stack in time O(2^n)
- OR fill table (with memoization becomes O(n * m)

-------------


K-th largest elem
http://www.geeksforgeeks.org/k-largestor-smallest-elements-in-an-array/

----------

https://www.geeksforgeeks.org/water-drop-problem/

precompute left and right array
or maintain 2 variables left_max and right_max at any point
https://www.geeksforgeeks.org/trapping-rain-water/

----------

https://www.geeksforgeeks.org/number-subarrays-product-less-k/

---------

https://www.geeksforgeeks.org/minimum-swaps-required-bring-elements-less-equal-k-together/
min number of swaps to bring clusters of numbers less than k together
sliding window


-----------

Range min query (RMQ)
https://www.geeksforgeeks.org/range-minimum-query-for-static-array/

1. build n^2 array for min of each range (i, j)
2. keep sq_root(n) array for min index
3. lookup(i, j) has min of arr[i] to arr[i + 2^j - 1]
4. segment tree

range product query
https://www.geeksforgeeks.org/range-product-queries-in-an-array/

https://www.geeksforgeeks.org/iterative-segment-tree-range-minimum-query/

segment tree stores as binary heap
https://www.geeksforgeeks.org/segment-tree-set-1-range-minimum-query/


-----------

https://www.geeksforgeeks.org/count-inversions-array-set-3-using-bit/

use BST
https://www.geeksforgeeks.org/count-smaller-elements-on-right-side/

number of next greater elem  - stack keeps index whose nge needed while moving from left to right
http://www.geeksforgeeks.org/number-nges-right/

https://www.geeksforgeeks.org/next-greater-frequency-element/

use stack, left to right
https://www.geeksforgeeks.org/the-stock-span-problem/

https://www.geeksforgeeks.org/maximum-profit-by-buying-and-selling-a-share-at-most-k-times/

https://www.geeksforgeeks.org/count-strictly-increasing-subarrays/

--------

rotate array

https://www.geeksforgeeks.org/block-swap-algorithm-for-array-rotation/

https://www.geeksforgeeks.org/search-an-element-in-a-sorted-and-pivoted-array/

------------

largest sum contiguous subarray  - KADANE
http://www.geeksforgeeks.org/largest-sum-contiguous-subarray/

max product of subarray with pos & neg
https://www.geeksforgeeks.org/maximum-product-subarray/

largest sum subarray
https://www.geeksforgeeks.org/largest-sum-contiguous-subarray/

using prefix sum

https://www.geeksforgeeks.org/maximum-subarray-sum-using-prefix-sum/

split array into equal sum sets

https://www.geeksforgeeks.org/print-equal-sum-sets-array-partition-problem/

https://www.geeksforgeeks.org/dynamic-programming-set-18-partition-problem/

min diff partition

https://www.geeksforgeeks.org/partition-a-set-into-two-subsets-such-that-the-difference-of-subset-sums-is-minimum/

-----------


-----------------

edit distance

https://www.geeksforgeeks.org/edit-distance-and-lcs-longest-common-subsequence/

search in array when adj diff is k

https://www.geeksforgeeks.org/searching-array-adjacent-differ-k/

------------

find second largest and then print all less than it
https://www.geeksforgeeks.org/find-elements-array-least-two-greater-elements/

https://www.geeksforgeeks.org/find-second-largest-element-array/

https://www.geeksforgeeks.org/find-the-largest-three-elements-in-an-array/

https://www.geeksforgeeks.org/k-th-smallest-absolute-difference-two-elements-array/

-----------

https://www.geeksforgeeks.org/minimum-number-of-jumps-to-reach-end-of-a-given-array/

--------

subsets - use binary number system
https://www.geeksforgeeks.org/power-set/

permutations



