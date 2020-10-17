
/*
TODO
Karumanchi Prob 11.40
page 280
*/

/*
    [ 3 5 8 9 10 12 ]
    max - min = even
              = od
              < 1, 2

    (max-min+1)/2 [0,1] = 0
                [0,2] = 1

    if elem > a[mid]
        go right - (min = mid + 1)
    else if elem < a[mid]
        go left (max = mid - 1)
    else
        return
*/

#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <assert.h>

using namespace std;

            // [7 8 - 0 1 2 3 4 5 6 ]
            // [2 3 4 5 6 7 8 - 0 1 ]
        //[0-9]
      //[0-5][6-9]

int findPivot(int arr[], int low, int high)
{
   // base cases
   if (high < low)  return -1;
   if (high == low) return low;
 
   int mid = (low + high)/2;   /*low + (high - low)/2;*/
   if (mid < high && arr[mid] > arr[mid + 1])
     return mid;
   if (mid > low && arr[mid] < arr[mid - 1])
     return (mid-1);
   if (arr[low] >= arr[mid])
     return findPivot(arr, low, mid-1);
   else
     return findPivot(arr, mid + 1, high);
}

int findElem(int elem, int set[], int& min, int& max)
{
    while (1)
    {
        if (min > max) return -1;

        int mid = (min + max)/2;
        cout << "mid=" << mid << ":min=" << min << ":max=" << max << endl;

        if (elem < set[mid])
        {
            max = mid - 1;
        }
        else if (elem > set[mid])
        {
            min = mid + 1;
        }
        else
        {
            return mid;
        }
    } 
}

int main(int argc, char* argv[])
{
    unsigned int seed = getpid();
    srand(seed);

    int NUM = atoi(argv[1]);
    int* set = (int*) malloc(sizeof(int) * NUM);
    int FROM = atoi(argv[2]);

    for (int i = 0; i < NUM; i++)
    {
        set[i] = rand_r(&seed) % 100;
    }
    std::sort(set, set + NUM);

    std::rotate(set, set + FROM, set + NUM);

    for (int i = 0; i < NUM; i++)
    {
        cout << set[i] << " ";
    }
    cout << endl;
    

    int min = 0;
    int max = NUM-1;
    int idx = -1;
    {
    //int elem;
    //cin >> elem;
    //idx = findElem(elem, set, min, max);
    }
    {
    idx = findPivot(set, min, max);
    }
    cout << "min=" << min << ":max=" << max << " found at " << idx << endl;
}


