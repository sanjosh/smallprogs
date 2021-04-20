/*

http://www.geeksforgeeks.org/print-all-combinations-of-points-that-can-compose-a-given-number/
*/
#include <iostream>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <stdio.h>
using namespace std;

#define ARR_SIZE 100
int arr[ARR_SIZE];

void printCombo(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

/*
void divideSum(int remainder, int curIndex)
{
    if (remainder == 0)
    {
        printCombo(arr, curIndex);
    }
    else if (remainder > 0)
    {
        for (int i = 1; i <= 3; i++)
        {
            arr[curIndex] =  i;
            if (remainder >= i) 
            {
                divideSum(remainder - i, curIndex + 1);
            }
        }
    }
}
*/

struct DS
{
    int remainder;
    int curIndex;
};

stack<DS> st;

void divideSum(int remainder, int curIndex)
{
    while (st.size())
    {
        DS a = st.pop(); 
    }
}

int main(int argc, char* argv[])
{
    bzero(arr, sizeof(arr)/sizeof(arr[0]));
    divideSum(atoi(argv[1]), 0);
}
