
/*

negative items

start with smallest example

approaches
1. create and combine sub-matrices - greedy 
2. divide and conquer - start with max, what can u remove to reduce sum?
2. find contiguous elements and then aggregate

go row by row, col by col

number of sub-matrices = 
row col shape = 
1,1 to 1,4
2,1 to 2,4
3,1 to 3,4
4,1 to 4,4

adding a row or col should not increase sum (i.e. row sum < 0)

only keep submatrices with negative sum

only grow sub-matrices around negative elements (starting from max negative)

create sub-matrices of negative elements

combine them if the cumulative sum is lesser

class matrix
{
    std::pair<int, int> start;
    std::pair<int, int> end;
};

matrix combine_matrix(matrix a, matrix b)
{
    new_start = min_row, min_col
    new_end = max_row, max_col
    
}

create initial set of submatrix of negative elements

for each negative element
{
    find negative element in same row or col
    create new matrix
}

tree<sum, matrix>

for each pair of smallest matrices
{
    if sum of new_matrix < matrix_a, matrix_b
}

----

Kadane algo

minSum of contiguous is applied to array containing sums of neighbouring columns

create sums for row 0 to row N for
col0, col01, col02, 
      col1,  col12 
             col2

e.g.
array[0] = sum for row 0, col12
array[1] = sum for row 1, col12

pass this cumulative sum of neighbouring columns array to kadane

it returns (start-row, end-row) which indicates contiguous submatrix (row L to row K, col 02)

https://www.geeksforgeeks.org/minimum-sum-submatrix-given-2d-array/

https://www.geeksforgeeks.org/maximum-sum-rectangle-in-a-2d-matrix-dp-27/

https://www.geeksforgeeks.org/smallest-sum-contiguous-subarray

*/
