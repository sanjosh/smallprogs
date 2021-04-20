
/* hackerrank gates distributing candies */

#include <cmath>
#include <cstdio>
#include <assert.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <list>
using namespace std;

int main() {
    /* The code required to enter n,k, candies is provided*/

    int N, K;
    int unfairness = 1000000000;
    cout << unfairness << endl;
    int curPos=-1;

    cin >> N >> K;
    vector<int> candies;

    for (int i=0; i<N; i++)
    { 
        int inCandy;
        cin >> inCandy;
        candies.push_back(inCandy);
    }
    
    std::sort(candies.begin(), candies.end());

    for (int i = 0; i <= candies.size() - K; i++)
    {
        int dist = candies[i+ K-1] - candies[i];
        assert(i + K -1 < candies.size());
        if (dist < unfairness)
        {
            //cout << "max=" << candies[i+K-1] << ":" << candies[i] << endl;
            unfairness = dist;
            curPos = i;
        }
    }

    cout << unfairness << endl;

    return 0;
}

