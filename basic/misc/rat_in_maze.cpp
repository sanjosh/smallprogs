
http://vijayinterviewquestions.blogspot.in/2007/07/solve-rat-in-maze-problem-using.html

 Solve the Rat In A Maze problem using backtracking.
This is one of the classical problems of computer science. There is a rat trapped in a maze. There are multiple paths in the maze from the starting point to the ending point. There is some cheese at the exit. The rat starts from the entrance of the maze and wants to get to the cheese.

This problem can be attacked as follows.




Have a m*m matrix which represents the maze.

For the sake of simplifying the implementation, have a boundary around your matrix and fill it up with all ones. This is so that you know when the rat is trying to go out of the boundary of the maze. In the real world, the rat would know not to go out of the maze, but hey! So, initially the matrix (I mean, the maze) would be something like (the ones represent the "exra" boundary we have added). The ones inside specify the obstacles.


111111111111111111111
100000000000000000001
100000010000000000001
100000010000000000001
100000000100001000001
100001000010000000001
100000000100000000001
100000000000000000001
111111111111111111111



The rat can move in four directions at any point in time (well, right, left, up, down). Please note that the rat can't move diagonally. Imagine a real maze and not a matrix. In matrix language



Moving right means adding {0,1} to the current coordinates.

Moving left means adding {0,-1} to the current coordinates.

Moving up means adding {-1,0} to the current coordinates.

Moving right means adding {1,0} to the current coordinates.



The rat can start off at the first row and the first column as the entrance point.

From there, it tries to move to a cell which is currently free. A cell is free if it has a zero in it.

It tries all the 4 options one-by-one, till it finds an empty cell. If it finds one, it moves to that cell and marks it with a 1 (saying it has visited it once). Then it continues to move ahead from that cell to other cells.

If at a particular cell, it runs out of all the 4 options (that is it cant move either right, left, up or down), then it needs to backtrack. It backtracks till a point where it can move ahead and be closer to the exit.

If it reaches the exit point, it gets the cheese, ofcourse.

The complexity is O(m*m).



Here is some pseudocode to chew upon


findpath()
{
Position offset[4];
Offset[0].row=0; offset[0].col=1;//right;
Offset[1].row=1; offset[1].col=0;//down;
Offset[2].row=0; offset[2].col=-1;//left;
Offset[3].row=-1; offset[3].col=0;//up;

// Initialize wall of obstacles around the maze
for(int i=0; i < m+1;i++)
maze[0][i] = maze[m+1][i]=1; maze[i][0] = maze[i][m+1]=1;

Position here;
Here.row=1;
Here.col=1;

maze[1][1]=1;
int option = 0;
int lastoption = 3;

while(here.row!=m || here.col!=m)
{
//Find a neighbor to move
int r,c;

while (option <= LastOption)
{
r=here.row + offset[position].row;
c=here.col + offset[option].col;
if(maze[r][c]==0)break;
option++;
}

//Was a neighbor found?
if(option <= LastOption)
{
path->Add(here);
here.row=r;here.col=c;
maze[r][c]=1;
option=0;
}
else
{
if(path->Empty())return(False);
Position next;
Path->Delete(next);
If(new.row==here.row)
Option=2+next.col - here.col;
Else { option = 3 + next.row - here.col;}
Here=next;
}
return(TRUE);
}
}

//=====================


http://www.geeksforgeeks.org/backttracking-set-2-rat-in-a-maze/
/*

TODOive Algorithm is to generate all paths from source to destination and one by one check if the generated path satisfies the constraints.

while there are untried paths
{
   generate the next path
   if this path has all blocks as 1
   {
      print this path;
   }
}

Backtrackng Algorithm

If destination is reached
    print the solution matrix
Else
    if (isSafe(x, y))
    {
        array[x, y] = 1
        if call Soln(x, y+1) return true
        if call Soln(x+1, y) return true
        array[x, y] = 0
    }
Implementation of Backtracking solution
*/

#include<stdio.h>
 
// Maze size
#define N 4
 
bool solveMazeUtil(int maze[N][N], int x, int y, int sol[N][N]);
 
/* A utility function to print solution matrix sol[N][N] */
void printSolution(int sol[N][N])
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
            printf(" %d ", sol[i][j]);
        printf("\n");
    }
}
 
/* A utility function to check if x,y is valid index for N*N maze */
bool isSafe(int maze[N][N], int x, int y)
{
    // if (x,y outside maze) return false
    if(x >= 0 && x < N && y >= 0 && y < N && maze[x][y] == 1)
        return true;
 
    return false;
}
 
/* This function solves the Maze problem using Backtracking.  It mainly uses
solveMazeUtil() to solve the problem. It returns false if no path is possible,
otherwise return true and prints the path in the form of 1s. Please note that
there may be more than one solutions, this function prints one of the feasible
solutions.*/
bool solveMaze(int maze[N][N])
{
    int sol[N][N] = { {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}
    };
 
    if(solveMazeUtil(maze, 0, 0, sol) == false)
    {
        printf("Solution doesn't exist");
        return false;
    }
 
    printSolution(sol);
    return true;
}
 
/* A recursive utility function to solve Maze problem */
bool solveMazeUtil(int maze[N][N], int x, int y, int sol[N][N])
{
    // if (x,y is goal) return true
    if(x == N-1 && y == N-1)
    {
        sol[x][y] = 1;
        return true;
    }
 
    // Check if maze[x][y] is valid
    if(isSafe(maze, x, y) == true)
    {
        // mark x,y as part of solution path
        sol[x][y] = 1;
 
        /* Move forward in x direction */
        if (solveMazeUtil(maze, x+1, y, sol) == true)
            return true;
 
        /* If moving in x direction doesn't give solution then
           Move down in y direction  */
        if (solveMazeUtil(maze, x, y+1, sol) == true)
            return true;
 
        /* If none of the above movements work then BACKTRACK:
            unmark x,y as part of solution path */
        sol[x][y] = 0;
        return false;
    }  
 
    return false;
}
 
// driver program to test above function
int main()
{
    int maze[N][N]  =  { {1, 0, 0, 0},
        {1, 1, 0, 1},
        {0, 1, 0, 0},
        {1, 1, 1, 1}
    };
 
    solveMaze(maze);
    getchar();
    return 0;
}
