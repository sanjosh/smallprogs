/*
Your algorithms have become so good at predicting the market that you now know what the share price 
of Wooden Orange Toothpicks Inc. (WOT) will be for the next N days.

Each day, you can either buy one share of WOT, sell any number of shares of WOT that you own, or not make any transaction at all. 
What is the maximum profit you can obtain with an optimum trading strategy?

Input

The first line contains the number of test cases T. T test cases follow:

The first line of each test case contains a number N. 
The next line contains N integers, denoting the predicted price of WOT shares for the next N days.

Output

Output T lines, containing the maximum profit which can be obtained for the corresponding test case.

Constraints

1 <= T <= 10
1 <= N <= 50000

All share prices are between 1 and 100000
*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

enum SType { None, Buy, Sell} ;

int maxProfit = 0;
int N = 0;
int* price = NULL;

int Trade(int dayNumber, SType type, int curShares, int curProfit)
{
    if (type == None)
    {   
    }
    else if (type == Sell)
    {   
        curProfit += curShares * price[dayNumber];
        curShares = 0;
    }
    else if (type == Buy) 
    {   
        curShares ++;
        curProfit -= price[dayNumber];
    }

    if (dayNumber != N)
    {
        int none = Trade(dayNumber + 1, None, curShares, curProfit);
        int buy = Trade(dayNumber + 1, Buy, curShares, curProfit);
        int sell = Trade(dayNumber + 1, Sell, curShares, curProfit);

        int curMax = none;
        if (curMax < buy) curMax = buy;
        if (curMax < sell) curMax = sell;

        curProfit +=curMax;
    }

    if (curProfit > maxProfit)
    {
        maxProfit = curProfit;
    }

    cout << string(dayNumber, '-') << dayNumber << ":" << type << ":" << curProfit << ":" << curShares << endl;

    return curProfit;
}

int main(int argc, char* argv[])
{
    N = 0;
    scanf("%d", &N);
    price = new int [N];

    for (int i = 0; i < N; i++)
    {
        cin >> price[i];
    }

    int ret = Trade(0, Buy, 0, 0);
    cout << maxProfit << endl;
}
