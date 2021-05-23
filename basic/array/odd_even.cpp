/*

 Given a set of integers, negative as well as non negative, You need to rearrange them such that negative and non negative integers at alternate positions.
 Constraints: order of all the negative and nonnegative integers must be the same as before if there are more negative integers, the integers in excess should occur at the end of the array and same goes for the non negative integers in case they are more in number.

 eg: -5,-2,5,2,4,7,1,8,0,-8
 output: -5,5,-2,2,-8,4,7,1,8,0

 Given an array of elements arrange the elements such that the odd elements are in the odd position and even elements are in the even position.
 - I gave him a two pass approach where i segregate first and then separate accordingly. But he asked the one pass solution. This was when my luck ran out. I know its pretty easy, but messed it up. And the guy was also adamant because even after 15 minutes of trial and error, he asked me to go on.


We can use two pointers approach. One traversing only even positions and one traversing only odd positions.
We will mover pointers till we find mismatch i.e. even number at position pointed by odd-pointer and odd number at position pointed by even-pointer.
We will swap numbers and continue traversing.

TODO


 */

#include <iostream>
#include <assert.h>
using namespace std;

#define N 10

int rotate(int arr[], int outofplace, int cur)
{
    assert(outofplace >= 0);
    assert(outofplace < cur);
    assert(cur < N);

    cout << " rotate from " << outofplace << ":" << cur << endl;
    char tmp = arr[cur];
    for (int i = cur; i > outofplace; i--)
    {
        arr[i] = arr[i-1];
        cout << "arr " << i << "=" << arr[i] << endl;
    }
    arr[outofplace] = tmp;
    cout << "arr " << outofplace << "=" << arr[outofplace] << endl;
}

void loop(int arr[])
{
    int lookfor = 0;
    int outofplace = -1;
    int index = 0;

    while (index < N)
    {
        if ((arr[index] > 0) && (lookfor == +1))
        {
                rotate(arr, outofplace, index);
                index = outofplace + 2;
                outofplace = -1;
                lookfor = 0;

        }
        else if ((arr[index] < 0) && (lookfor == -1))
        {
                rotate(arr, outofplace, index);
                index = outofplace + 2;
                outofplace = -1;
                lookfor = 0;
        }

        // have to re-evaluate after rotation
        if (outofplace == -1)
        {
            if ((arr[index] > 0) && (index % 2 == 0))
            {
                outofplace = index;
                lookfor = -1;
            }
            else if ((arr[index] < 0) && (index % 2 == 1))
            {
                outofplace = index;
                lookfor = +1;
            }
        }

        index ++;

    }

}

int main()
{
    //int arr[] = {-5, 3, 4, 5, -6, -2, 8, 9, -1, -4};
    int arr[] = {-5, -3, -4, -5, -6, 2 , 8, 9, 1 , 4};

    for (int i = 0; i < N; i++)
        cout << arr[i] << " ";
    cout << endl;

    loop(arr);

    for (int i = 0; i < N; i++)
        cout << arr[i] << " ";
    cout << endl;
}

