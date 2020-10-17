

TODO

An improvement to the pick the middle algorithm is to do a binary search on the diagonal from the upper left to lower right, and use the two adjacent values spanning the target to eliminate 1/2 of the matrix. This algorithm takes 1/2*N*log2(N) comparisons, which is twice as fast as binary search on each row, though still far from optimal, and if the matrix doesn't fit into cache, it will thrash memory much worse than a binary search on each row.

http://www.geeksforgeeks.org/search-in-row-wise-and-column-wise-sorted-matrix/
