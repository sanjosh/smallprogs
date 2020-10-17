
/*
TODO
Given a matrix consisting of 0's and 1's, find the largest connected component consisting of 1

http://www.careercup.com/question?id=5998719358992384

Another algo using makeset, union, find

for (int i =0; i < n; i++)
{
    for (int j =0; j < n; j++)
    {
        if (a[i][j])
        {
            makeset(i, j)

            // these are all predecessors in scan and must be in the SET
            for (x,y) in (i-1,j-1), (i-1, j), (i-1, j+1), (i, j-1)
            {
                union(x,y) with (i, j)
            }
        }
    }
}


*/
#include <iostream>
#include <stdlib.h>
using namespace std;

#define ASZ 5
int* mat[ASZ];
int parent[ASZ][ASZ];
int count[ASZ][ASZ];

int NeighbourHasParent(int* mat[ASZ], int n, int i, int j)
{
    if (i > 0)
    {
        int start = j;
        int end = j;
        if (j != 0) start = j-1;
        if (j != n-1) end = j+1;

        int m = -1;
        for (int k = start; k <= end; k++)
        {
            if (parent[i-1][k])
            {
                if (m==-1)
                {
                    parent[i][j] = parent[i-1][k];
                    count[i-1][k] ++;
                    cout << "setting " << i << ":" << j << " to " << i-1 << ":" << k << endl;
                    m = k;
                }
                else
                {
                    parent[i-1][k] = parent[i][j];
                    count[i-1][m] += count[i-1][k];
                    cout << "setting " << i-1 << ":" << k << " to " << i << ":" << j << endl;
                }
            }
        }
    }

    if (j > 0)
    {
        if (parent[i][j-1]) 
        {            
            parent[i][j] = parent[i][j-1];
            count[i][j-1] ++;
            cout << "setting " << i << ":" << j << " to " << i << ":" << j-1 << endl;
            return 0;
        }
    }

    parent[i][j] = ((i+1)*n) + (j + 1);
    count[i][j] ++;
    cout << "setting " << i << ":" << j << " to itself" << endl;

    return 0;
}

int largest(int* mat[ASZ], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            parent[i][j] = 0;
            count[i][j] = 0;

            if (mat[i][j])
            {
                NeighbourHasParent(mat, n, i, j);
            } 
        }            
    }        
}

void printmat()
{
    for (int i = 0; i < ASZ; i++)
    {
        for (int j = 0; j < ASZ; j++)
        {                
            cout << mat[i][j] << " ";
        }                
        cout << endl;
    }           
}

void printcount()
{
    for (int i = 0; i < ASZ; i++)
    {
        for (int j = 0; j < ASZ; j++)
        {                
            cout << count[i][j] << " ";
        }                
        cout << endl;
    }           
}

void printpar()
{
    for (int i = 0; i < ASZ; i++)
    {
        for (int j = 0; j < ASZ; j++)
        {                
            cout << parent[i][j] << " ";
        }                
        cout << endl;
    }           
}


int main(int argc, char* argv[])
{
    unsigned int seed= getpid(); 
    srand(seed);
    for (int i = 0; i < ASZ; i++)
    {
        mat[i] = new int[ASZ];
        for (int j = 0; j < ASZ; j++)
            mat[i][j] = (rand_r(&seed) & 0x01) ? 1 : 0;
    }            
    printmat();

    largest(mat, ASZ);

    printmat();
    printpar();
    printcount();
}
