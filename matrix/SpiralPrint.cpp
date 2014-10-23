/*

Print matrix in spiral form
Exploit memory layout to change step sizes 

*/

#include <iostream>
#include <iomanip>
#include <stdlib.h>
using namespace std;


// Pass as
int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "enter number=n as size of the array" << endl;
        exit(1);
    }

    int ARSZ = atoi(argv[1]);
    int Matrix[ARSZ][ARSZ];

    // Initialize matrix
    for (int i = 0; i < ARSZ; i++)
    {
        for (int j = 0; j < ARSZ; j++)
        {
            cout << setw(3) << (Matrix[i][j] = (i*ARSZ) + j) << " "; 
        }
        cout << endl;
    }

    // Exploit the memory layout of the 2D array to do spiral print
    // Change Stepsize as we progress along the border
    const int StepSize[] = {1, ARSZ, -1, -ARSZ};

    int *StartPos = (int*)Matrix;
    
    int BorderSize = ARSZ - 1;
    while (BorderSize >= 0)
    {
        cout << *StartPos << endl;

        int *CurPos = StartPos;
            
        if (BorderSize <= 0) break;

        for (int i = 0; i < 4; i++) // 4 because 2D Matrix has 4 borders
        {
            for (int k = 0; k < BorderSize; k++)
            {
                CurPos += StepSize[i];
                if (CurPos == StartPos) 
                {
                    break; // reached start, decrement BorderSize now
                }
                cout << *CurPos << endl;
            }
        }
        StartPos += (1 + ARSZ); // new Start is one row and column down
        BorderSize -= 2;
    }
}
