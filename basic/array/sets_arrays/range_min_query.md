
for array A[0...n]

## basic relations

rangemin(i, j) = min( rangemin(i, j-1), A[j] )

OR

rangemin(i, j) = min( rangemin(i + 1, j), A[i] )

## problem

what are the minimum number of ranges to store to satisfy any query
* without looking at individual elements
* or looking at least number of individual elements

max number of ranges is n(n-1)/2 = n^2

## relation for union ranges

if ranges are overlapping,  i < j < k < l

rangemin(i, l) = min(rangemin(i, k), rangemin(j, l))

## relation for intersecting ranges

if ranges are overlapping,  i < j < k < l

assume
1. j = i + 1, 
2. l = k + 1

you only have rangemin[i, k] and rangemin[j, l] computed

how to compute 

rangemin(j, k) = ?? from rangemin[i, k] and rangemin[j, l]

cannot do without checking individual elements since A[i] could be less than A[i+1,...l]

## how to remove elements from a precomputed range ?

say i < j < k

rangemin(i, j) = can it be computed from rangemin(i, k)

you have to compute for all(i, j), since the element to be removed in (j, k) can be less than all elements in (i, j) range

# storage choices for range min query

QED : since intersection of ranges not possible for min operator, you have to use solutions
1. store overlapping ranges for each starting point
2. divide array into non-overlapping ranges and add extra elements as required

## non-overlapping optimized for square root intervals

each interval is square root(N)

for overlapping query interval, 
1. need to add extra elements
2. use all ranges within query interval

## overlapping 2D table with power-of-two sizes

O(1) time

store array of ranges for each starting point and power-of-two size
* start = i for i = 0 to n
* size = 2^j for j = 0 to Log(n))

```
table[0][3] = min(0, 7)
```

to fill (L, R) entry, get min of (L, R-1) and (L + 2^j-1, R-1)

e.g. (0, 7) = min (0, 3) and (4, 7)

to find (L, R) do min of ([L, closest power 2 to R], [closest power 2 to L, R])


## segment tree

store min of range inside non-leaf nodes

divide into two

if range within query
  return value in node
else
  return min of both nodes


https://www.geeksforgeeks.org/range-minimum-query-for-static-array/
