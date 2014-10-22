/*

 Given a set of integers, negative as well as non negative, You need to rearrange them such that negative and non negative integers at alternate positions.
 Constraints: order of all the negative and nonnegative integers must be the same as before if there are more negative integers, the integers in excess should occur at the end of the array and same goes for the non negative integers in case they are more in number.

 eg: -5,-2,5,2,4,7,1,8,0,-8
 output: -5,5,-2,2,-8,4,7,1,8,0

http://www.geeksforgeeks.org/amazon-interview-set-118-campus-internship/
http://www.geeksforgeeks.org/amazon-interview-set-114-campus-internship/

My soln posted at :
http://www.geeksforgeeks.org/rearrange-array-alternating-positive-negative-items-o1-extra-space/

 */

#include <iostream>
#include <assert.h>
using namespace std;

// right rotate all elements between [outofplace, cur]
void rightrotate(int arr[], int N, int outofplace, int cur)
{
    assert(outofplace >= 0);
    assert(outofplace < cur);
    assert(cur < N);

    char tmp = arr[cur];
    for (int i = cur; i > outofplace; i--)
    {
        arr[i] = arr[i-1];
    }
    arr[outofplace] = tmp;
}

/* 
 * Worst case is when all positive elements precede all negative elements
 * then rightrotate() would be called n/2 times
 * and there would be [(n/2)(n/2+1)]/2 item movements or O(n^2)
 */
void recombine(int arr[], int N)
{
    int outofplace = -1;

    for (int index = 0; index < N; index ++)
    {
        if (outofplace >= 0)
        {
            // find the item which must be moved into the out-of-place entry
            // if out-of-place entry is positive and current entry is negative
            // OR if out-of-place entry is negative and current entry is negative
            // then right rotate
            //
            // [...-3, -4, -5, 6...] -->   [...6, -3, -4, -5...]
            //      ^                                  ^
            //      |                                  |
            //   old outofplace        -->          new outofplace
            //
            if (((arr[index] >= 0) && (arr[outofplace] < 0))
                || ((arr[index] < 0) && (arr[outofplace] >= 0)))
            {
                rightrotate(arr, N, outofplace, index);

                // if index is more than 2 steps ahead of out-of-place entry
                // the new out-of-place entry will be 2 steps to the right
                // otherwise the current rotate was a swap between 2 elements
                // and outofplace will get recalculated below
                if (index - outofplace > 2)
                    outofplace = outofplace + 2;
                else
                    outofplace = -1;
            }
        }

        // if no entry has been flagged out-of-place
        if (outofplace == -1)
        {
            // check if current entry is out-of-place
            if (((arr[index] >= 0) && (!(index & 0x01)))
                || ((arr[index] < 0) && (index & 0x01)))
            {
                outofplace = index;
            }
        }
    }
}

int main()
{
    //int arr[N] = {-5, 3, 4, 5, -6, -2, 8, 9, -1, -4};
    //int arr[] = {-5, -3, -4, -5, -6, 2 , 8, 9, 1 , 4};
    int arr[] = {5, 3, 4, 2, 1, -2 , -8, -9, -1 , -4};
    //int arr[] = {-5, 3, -4, -7, -1, -2 , -8, -9, 1 , -4};
    //int arr[] = {-5,-2,5,2,4,7,1,8,0,-8};

    int N = sizeof(arr)/sizeof(arr[0]);

    for (int i = 0; i < N; i++)
        cout << arr[i] << " ";
    cout << endl;

    recombine(arr, N);

    for (int i = 0; i < N; i++)
        cout << arr[i] << " ";
    cout << endl;
}

