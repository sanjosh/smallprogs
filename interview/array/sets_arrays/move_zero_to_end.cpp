
// http://www.geeksforgeeks.org/amazon-interview-set-125-on-campus-for-internship/

#include <iostream>
using namespace std;

void swap(int arr[], int front, int back)
{
    int tmp = arr[front];
    arr[front] = arr[back];
    arr[back] = tmp;
}

void minswap(int arr[], size_t n)
{
    int back = n-1;

    while (arr[back] == 0) back --;

    int front = 0;

    while (front < back)
    {
        if (arr[front] == 0)
        {
            swap(arr, front, back);
            back --;
            while (arr[back] == 0) back --;
        }
        front ++;
    }
}

int main(int argc, char* argv[])
{
    int arr[] = { 1, 9, 8, 0, 0, -2, -6, 1, 0};
    int n = sizeof(arr)/sizeof(arr[0]);

    minswap(arr, n);

    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}
