#include <iostream>
#include <stdlib.h>
#include <iomanip>
using namespace std;

#define N 10
#define MAX 1000000

int pred[N][N];

int findJump(int selected[][N], int arr[][N], int i, int j)
{
    if ((i >= N) || (j >= N)) 
        return MAX;


    if (i == N-1 && j == N-1) 
    {
        return (selected[i][j] = 0);
    }

    int val = arr[i][j];
    int min = MAX;
    int selj = -1;
    int seli = -1;

    if (selected[i][j] != MAX)
    {
        return selected[i][j];
    }

    if (val == 0)
    {
        return MAX;
    }

    cout << "choosing for " << i << ":" << j << endl;
    for (int k = 0; k <= val; k++)
    {
        int jmp = findJump(selected, arr, i + k, j + val - k);
        if (jmp + 1 < min) 
        {
            min = jmp + 1;
            seli = i + k;
            selj = j + val -k;
        }
    }            

    if (seli != -1)
    {
        pred[i][j] = (seli << 8) | selj;
        //cout << "selected: " << seli << ":" << selj << ":pred=" << pred[i][j] << ":val=" << min << endl;
    }
    return (selected[i][j] = min);
}

int main(int argc, char* argv[])
{
    int arr[N][N];
    int selected[N][N];

    unsigned int seed = getpid();
    srand(seed);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            pred[i][j] = -1;
            selected[i][j] = MAX;
            arr[i][j] = (rand_r(&seed) & 0x01) + 1;
            arr[N-1][N-1] = 0;
            arr[0][0] = 1;
            cout << arr[i][j] << " ";
        }            
        cout << endl;
    }

    int jmp = findJump(selected, arr, 0, 0);
    cout << jmp << endl;

    cout << "SELECTED" << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << setw(8) << selected[i][j] << " ";
        }
        cout << endl;
    }
    cout << "PRED" << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (pred[i][j] != -1)
            {
                int seli = (pred[i][j] >> 8);
                int selj = pred[i][j] & ((1<<8)-1);
                cout << setw(10) << seli << ":" << selj << " ";
            }
            else
                cout << setw(10) << -1 << ":" << -1 << " ";
        }
        cout << endl;
    }
}
