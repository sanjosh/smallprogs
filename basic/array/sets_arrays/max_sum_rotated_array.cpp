
/* 
    http://www.geeksforgeeks.org/facebook-interview-set-2-campus-interview-internship/

Facebook problem
    n trees in a circle 
    birds sitting on tree for 0.5 sec
    gain value from each tree
    and travel to next tree in 0.5 sec 
    maximize value gained
*/

#include <queue>
#include <iostream>
using namespace std;

int maxVal = 0;
int curSum = 0;
int endIndex = 0;
queue<int> q;
int n;

int main(int argc, char* argv[])
{
    int arr[] = {9, 7, 10, 4, 5, 1, 8, 3, 1, 1, 10};
    n = sizeof(arr)/sizeof(arr[0]);

    //q.reserve(n);

    q.push(arr[0]);
    q.push(arr[1]);
    q.push(arr[2]);

    curSum = maxVal= arr[0] + arr[1] + arr[2];
    endIndex = 2;

    for (int i = 3; i < n+2; i++)
    {
        int offset = i % n;

        int rem = q.front();
        q.pop();
        q.push(arr[offset]);

        curSum += (arr[offset] - rem);
        if (curSum > maxVal) 
        {
            maxVal = curSum;
            endIndex = offset;
        }
    }

    cout << "max=" << maxVal << ":endIndex=" << endIndex << endl;
}
