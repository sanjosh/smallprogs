/*


sumOf(N) = 1 + sumOf(N - coin) for all coins < N
         = 0 if N < minCoin

1 - 1
2 - [11], [2]
3 - [1[1[1]]], [3], [12]

ordering is required
so only pick coins >= currentCoin


*/


#include <iostream>
#include <vector>

using namespace std;

std::vector<int32_t> coins = {1, 2, 3};

/**
 * wrong - do not start with zero curIdx and increment it
 */
int SumOf(int N, int curIdx, int level)
{
    int count = 0;
    cout << level << ":" << N << "," << curIdx << endl;
    if (N == 0) {
        return 1; // reached leaf node which makes a unique path - so return 1
    }
    for (int i = curIdx; i < coins.size(); i++)
    {
        if (N >= coins[i])  {
            count += SumOf(N - coins[i], i, level + 1);
        }
    }
    return count;
}

int SumOfRev(int Sum, int numElem, int level)
{
    cout << "level=" << level << ":" << Sum << ":" << numElem << endl;
    if (Sum == 0) return 1;

    if (Sum < 0) return 0;

    if (numElem <= 0 && Sum >= 1) return 0; // no coins

    return SumOfRev(Sum, numElem - 1, level + 1) // excluding elem
           + SumOfRev(Sum - coins[numElem - 1], numElem, level + 1); // including elem
}

int SumOfRevDP()
{
    int table[4][coins.size()];

    for (int j = 0; j < coins.size(); j++)
    {
        table[0][j] = 1; // 0 sum can always be formed by excluding each element
    }

    for (int sum = 1; sum < 4; sum ++)
    {
        for (int coinIdx = 0; coinIdx < coins.size(); coinIdx ++)
        {
            int includingElem = 0;
            int excludingElem = 0;
            if (sum >= coins[coinIdx]) {
                // previous row, same col - this will complete sum
                includingElem = table[sum - coins[coinIdx]][coinIdx];
            }

            if (coinIdx >= 1) {
                // same row, previous col - sum was already completed
                excludingElem = table[sum][coinIdx - 1];
            }
            table[sum][coinIdx] = includingElem + excludingElem;
            cout << table[sum][coinIdx] << ",";
        }
        cout << endl;
    }
    return table[3][coins.size() - 1];
}

int main()
{
    cout << SumOfRevDP() << endl;
}

