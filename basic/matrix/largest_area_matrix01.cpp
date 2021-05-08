
/*
TODO
See karumanchi
chap 19 - prob 41
chap 5 - prob 24

https://www.geeksforgeeks.org/maximum-size-rectangle-binary-sub-matrix-1s/

https://www.geeksforgeeks.org/maximum-size-sub-matrix-with-all-1s-in-a-binary-matrix/

can submatrices be combined ? divide and conquer
can previous submatrix be grown

Approach 1 :  record sums for (0, 0) to (i, j)

Sum[i][j] holds sum from (0,0) to (i, j)

If M[i][j] is 1 then
   Sum[i][j] = min(Sum[i][j-1], Sum[i-1][j], Sum[i-1][j-1]) + 1
else
   Sum[i][j] = 0

to find min (i, j)
 for(i = max_i; i > max_i - max_sum; i--)

 Approach 2 : largest area under histogram


*/
