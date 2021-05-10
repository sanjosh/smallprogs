
//http://www.geeksforgeeks.org/backtracking-set-1-the-knights-tour-problem/

#include<stdio.h>
#define N 8
 
int solveKTUtil(int x, int y, int movei);
 
/* A utility function to check if i,j are valid indexes for N*N chessboard */
int isSafe(int x, int y, int sol[N][N])
{
    if ( x >= 0 && x < N && y >= 0 && y < N && sol[x][y] == -1)
        return 1;
    return 0;
}
 
/* A utility function to print solution matrix sol[N][N] */
void printSolution(int sol[N][N])
{
    for (int x = 0; x < N; x++)
    {
        for (int y = 0; y < N; y++)
            printf(" %2d ", sol[x][y]);
        printf("\n");
    }
}
 
    /* xMove[] and yMove[] define next move of Knight.
       xMove[] is for next value of x coordinate
       yMove[] is for next value of y coordinate */
    int xMove[N] = {  2, 1, -1, -2, -2, -1,  1,  2 };
    int yMove[N] = {  1, 2,  2,  1, -1, -2, -2, -1 };

int sol[N][N];


/* This function solves the Knight Tour problem using Backtracking.  This
function mainly uses solveKTUtil() to solve the problem. It returns false if
no complete tour is possible, otherwise return true and prints the tour.
Please note that there may be more than one solutions, this function
prints one of the feasible solutions.  */
bool solveKT()
{
 
    /* Initialization of solution matrix */
    for (int x = 0; x < N; x++)
        for (int y = 0; y < N; y++)
            sol[x][y] = -1;
 
 
    // Since the Knight is initially at the first block
    sol[0][0]  = 0;
 
    /* Start from 0,0 and explore all tours using solveKTUtil() */
    if (solveKTUtil(0, 0, 1) == false)
    {
        printf("Solution does not exist");
        return false;
    }
    else
        printSolution(sol);
 
    return true;
}

 
/* A recursive utility function to solve Knight Tour problem */
int solveKTUtil(int x, int y, int movei)
{
   int k, next_x, next_y;

   if (movei == N*N)
    {
        printf("reached here\n");
       return true;
    }
 
   /* Try all next moves from the current coordinate x, y */
   for (k = 0; k < 8; k++)
   {
       next_x = x + xMove[k];
       next_y = y + yMove[k];
       if (isSafe(next_x, next_y, sol))
       {
         sol[next_x][next_y] = movei;
         if (solveKTUtil(next_x, next_y, movei+1) == true)
             return true;
         else
             sol[next_x][next_y] = -1;// backtracking
       }
   }
 
   //printf("move=%d (%d %d) failed\n", movei, x, y);
   return false;
}
 
/* Driver program to test above functions */
int main()
{
    solveKT();
    getchar();
    return 0;
}

