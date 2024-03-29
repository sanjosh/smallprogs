
find all runs of the number
do merge sort on them in k-ary fashion

1) bubble sort - O(n^2)

2) selection sort - O(n^2) - better to use heapsort

3) insertion -  O(n^2)
    card players take each card and put it in right place
    for i = 1 to length(A)
    j = i
    while j > 0 and A[j-1] > A[j]
        swap A[j] and A[j-1]
        j = j - 1
    Best cast - already sorted
    Worst case - rev sorted

4) non-comparision sort
    bucketb O(n+k) average, O(n^2) worst where k =num buckets
    radix 
    counting O(n+k)

5) Quicksort 
    worst case O(n^2) occurs when largest or smallest elem is chosen as pivot
    bcos then no movement occurs in subsection
    so make median = pivot

6) Introsort (D.Mussey ?)
    switch to heapsort when qsort tree depth goes too high
    switch to insertion sort for small num of elem

7) mergesort
    Worst case when max number of comparisons
    http://stackoverflow.com/questions/24594112/when-will-the-worst-case-of-merge-sort-occur/24594419#24594419

8) Timsort : sort the small pieces using insertion sort, then merge pieces using merge sort

9) Counting sort : if elem in range n (CDF)

keep count of each elements
cumulative count indicates position in array

10) Radix sort : if elem in range 1 to n^2

from lsb to msb, sort array using counting sort as subroutine

11) Cartesian tree sorting (when input almost sorted)

https://www.geeksforgeeks.org/cartesian-tree-sorting/

quick sort vs merge sort

1) quick sort is space constant; merge requires 2N + 
2) quick sort worst case is O(n^2) - when sorted or have duplicates - do random shuffle or pick pivot
3) quick sort faster in practice bcos inner loop fast on most architecture
3) ave and best case for both is O(n.logn)
5) both use insertion sort for small range
6) merge sort good for external sorting
7) both are stable sort ( order retained for duplicate elem)
8) what is the constant term in O - O(cn)

http://www.cprogramming.com/tutorial/computersciencetheory/sortcomp.html

how to parallelize on modern pipelined processors

======

sorting

comparison : lower bound of Omega(n.logn) on any comparison based sort
        using decision-tree model
    insertion : like card player
    shell sort - extension of insertion sort
    bubble : swap adjacent elements
    quick-sort - pivot (use median), use insertion sort for small
    merge
    heapsort

non-comparison sorting
    counting sort - assume numbers in range [0..k]
    radix - sort by lsb, then next bit and so on
    bucket sort - assume input probab distribution - put numbers into buckets and then use insertion sort within each bucket
    bucket sort runs in linear time as long as sum of squares of bucket sizes is linear in total number of elements

==============
Bubble:
for i=1 to n-1
    for j = n to (i+1)  
        if A[j] < A[j-1]
            swap(A[j], A[j-1])

==============
Insertion sort:
Running time depends on number of inversions - bcos u are inserting into sorted array

