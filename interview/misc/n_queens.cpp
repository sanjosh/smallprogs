/*

eight queens 
( same diag if row1-row1==col1-col2) 

https://www.cs.sunysb.edu/~skiena/392/programs/8-queens.c
http://vijayinterviewquestions.blogspot.in/2007/07/what-is-8-queens-problem-write-c.html

http://www.geeksforgeeks.org/backtracking-set-3-n-queen-problem/

TODO
*/

Place(Row k, Col i)
{
    for j = 1 to k-1
    {
        if x[j] == i OR abs(x[j]-i) = abs(j-k)
            return false
    }
    return true
}

NQueens(Row k, MatrixSize n)
{
    for i = 1 to n 
    {
        if Place(k, i)  // bounding func
        {
            x[k] = i

            if (k==n) then 
                write x[1..n]
            else 
                NQueens(k+1, n)
        }
    }
}

==============

from stanford.edu

bool Solve(Grid<bool> &board, int col)
{
    if (col >= board.numCols()) return true;
    // base case

    for (int rowToTry = 0; rowToTry < board.numRows(); rowToTry++) 
    {
        if (IsSafe(board, rowToTry, col)) 
        {
            PlaceQueen(board, rowToTry, col);
            // try queen here
            if (Solve(board, col + 1)) return true;
            // recur to place rest
            RemoveQueen(board, rowToTry, col);
            // failed, remove, try again
        }
    }
    return false;
}

//////////

Backtracking Algorithm
The idea is to place queens one by one in different columns, starting from the leftmost column. When we place a queen in a column, we check for clashes with already placed queens. In the current column, if we find a row for which there is no clash, we mark this row and column as part of the solution. If we do not find such a row due to clashes then we backtrack and return false.

1) Start in the leftmost column
2) If all queens are placed
    return true
3) Try all rows in the current column.  Do following for every tried row.
    a) If the queen can be placed safely in this row then mark this [row, 
        column] as part of the solution and recursively check if placing  
        queen here leads to a solution.
    b) If placing queen in [row, column] leads to a solution then return 
        true.
    c) If placing queen doesn't lead to a solution then umark this [row, 
        column] (Backtrack) and go to step (a) to try other rows.
3) If all rows have been tried and nothing worked, return false to trigger 
    backtracking.

Implementation of Backtracking solution
#define N 4
#include<stdio.h>
 
/* A utility function to print solution */
void printSolution(int board[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf(" %d ", board[i][j]);
        printf("\n");
    }
}
 
/* A utility function to check if a queen can be placed on board[row][col]
   Note that this function is called when "col" queens are already placeed
   in columns from 0 to col -1. So we need to check only left side for
   attacking queens */
bool isSafe(int board[N][N], int row, int col)
{
    int i, j;
 
    /* Check this row on left side */
    for (i = 0; i < col; i++)
    {
        if (board[row][i])
            return false;
    }
 
    /* Check upper diagonal on left side */
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
    {
        if (board[i][j])
            return false;
    }
 
    /* Check lower diagonal on left side */
    for (i = row, j = col; j >= 0 && i < N; i++, j--)
    {
        if (board[i][j])
            return false;
    }
 
    return true;
}
 
/* A recursive utility function to solve N Queen problem */
bool solveNQUtil(int board[N][N], int col)
{
    /* base case: If all queens are placed then return true */
    if (col >= N)
        return true;
 
    /* Consider this column and try placing this queen in all rows
       one by one */
    for (int i = 0; i < N; i++)
    {
        /* Check if queen can be placed on board[i][col] */
        if ( isSafe(board, i, col) )
        {
            /* Place this queen in board[i][col] */
            board[i][col] = 1;
 
            /* recur to place rest of the queens */
            if ( solveNQUtil(board, col + 1) == true )
                return true;
 
            /* If placing queen in board[i][col] doesn't lead to a solution
               then remove queen from board[i][col] */
            board[i][col] = 0; // BACKTRACK
        }
    }
 
     /* If queen can not be place in any row in this colum col
        then return false */
    return false;
}
 
/* This function solves the N Queen problem using Backtracking.  It mainly uses
solveNQUtil() to solve the problem. It returns false if queens cannot be placed,
otherwise return true and prints placement of queens in the form of 1s. Please
note that there may be more than one solutions, this function prints one of the
feasible solutions.*/
bool solveNQ()
{
    int board[N][N] = { {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
 
    if ( solveNQUtil(board, 0) == false )
    {
      printf("Solution does not exist");
      return false;
    }
 
    printSolution(board);
    return true;
}
 
// driver program to test above function
int main()
{
    solveNQ();
 
    getchar();
    return 0;
}


