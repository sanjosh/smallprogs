
/* view it as a tree */

/*

bool comp(Seq& arr)
{
    Seq newarr;
    int j = 0;
    bool changed = false;
    for (int i = 0; i < n-2; i+=2)
    {
        int sum = (arr[i] + arr[i+1] + arr[i+2]);
        if (sum > 0)
        {
            newarr[j++] = sum;
            changed = true;
        }
        else
        {
            newarr[j++] = arr[i];
            newarr[j++] = arr[i+1];
            newarr[j++] = arr[i+2];
        }
    }
    arr = newarr;
    return changed;
}

*/

// Kadane algo

#include <vector>
#include <stdlib.h>
#include <iostream>
using namespace std;
typedef vector<int> Seq;

int sequence(std::vector<int> const & numbers)
{
        // Initialize variables here
        int max_so_far  = numbers[0], max_ending_here = numbers[0];
 
        // OPTIONAL: These variables can be added in to track the position of the subarray
        size_t begin = 0;
        size_t begin_temp = 0;
        size_t end = 0;
 
        // Find sequence by looping through
        for(size_t i = 1; i < numbers.size(); i++)
        {
                // calculate max_ending_here
                if(max_ending_here < 0)
                {
                // if it falls below zero, start count afresh
                        max_ending_here = numbers[i];
                        begin_temp = i;
                        cout << "reset max=" << max_ending_here << " at i=" << i << endl;

                }
                else
                {
                        max_ending_here += numbers[i];
                        cout << "max=" << max_ending_here << " at i=" << i << endl;
                }
 
                // calculate max_so_far
                if(max_ending_here >= max_so_far )
                {
                        max_so_far  = max_ending_here;
 
                        begin = begin_temp;
                        end = i;
                        cout << "NOW max=" << max_so_far << ":begin=" << begin << ":end=" << end << endl;
                }
        }
        return max_so_far ;
}

int main()
{
    unsigned int seed = getpid();
    srand(seed);

    Seq arr;

    for (int i = 0; i < 20; i++)
    {
        int num = rand_r(&seed) % 20;
        if (i%2) num = -num;
        arr.push_back(num);
        cout << num << " ";
    }
    cout << endl;

    int max = sequence(arr);
    cout << max << endl;
}
