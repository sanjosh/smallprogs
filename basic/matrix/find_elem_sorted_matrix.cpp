
/*
https://www.geeksforgeeks.org/search-in-row-wise-and-column-wise-sorted-matrix/
    [1, 4, 6]
    [5, 6, 12]
    [11, 35, 51]

cases
1. < first elem
2. > corner elem of matrix
3. multiple 
4. not found

------------
for each row = 1 to n
   if row.first < elem
       break
   binsearch(row)

------------
second approach : 

start from top right or bottom left
while row and col in range
if mat > x; reduce col
if max < x; increase row
else found

------------
third approach :
binsearch diagonal returns [x,x] [x+1,x+1]
then search from 

start_row, start_col
 x-1,       x  (until x-1 < 0
 x,         x
 x+1,       0 




*/

#include <iostream>
using namespace std;

int binsearch(int arr[], int n, int elem)
{
    int left = 0;
    int right = n-1;

    while (left <= right) {
        int mid = left + (right - left)/2;
        if (arr[mid] < elem)
            left = mid + 1;
        else if (arr[mid] > elem)
            right = mid - 1;
        else
            return mid;
    }
    return -1;
}

int matsearch(int arr[][3], int n, int elem)
{
    for (int row = 0; row < n; row ++)
    {
        if (arr[row][0] > elem) {
            break;
        }
        if (arr[row][n-1] < elem) {
            continue;
        }
        int x = binsearch(arr[row], n, elem);
        if (x != -1) {
            cout << "found=" << row << "," << x << endl;
            return x;
        }
    }
    return -1;
}

int matsearch2(int arr[][3], int n, int elem)
{
    int row = 0;
    int col = 2;

    while (row < 3 && col >= 0)
    {
        if (arr[row][col] == elem) {
            cout << "found=" << row << "," << x << endl;
            return row;
        } else if (arr[row][col] < elem) {
            row ++;    
        } else {
            col --;
        }
    }
    return -1;
}

int main()
{
    int arr[3][3] =
    {
        {2, 3, 5},
        {5, 6, 10},
        {10, 15, 20},
    };

    int search[] = {1, 2, 6, 7, 47};
    for (int i = 0; i < sizeof(search)/sizeof(search[0]); i ++)
        cout << matsearch2(arr, 3, search[i]) << endl;
}

  /*
  std::array<std::array<int,3>,2> a {{
    {{1,2,3}},
    {{4,5,6}}
 }};

 nxm matrix
 vector<vector<int>>  matrix(n, vector<int>(m, -1));

 */
