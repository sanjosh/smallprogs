#include <iostream>
using namespace std;

/*
    maximize profit by completing jobs before deadline
 */

int n = 10;

int deadline_job[] = { 1, 1, 1, 2, 2, 2, 3, 3, 3, 3};
int profit[] = { 4, 1, 3, 44, 22, 12, 12, 9, 23, 10 };

int deadline_time = 4;

int get_profit(int idx, int cur_time)
{
    // base conditions
    if (idx >= 10) {
        return 0;
    } 
    if (cur_time >= deadline_time) {
        return 0;
    }

    // yes no decision tree
    int yes = 0;
    if (deadline_job[idx] <= cur_time) {
        yes = profit[idx] + get_profit(idx + 1, cur_time + 1);
    }
    int no = get_profit(idx + 1, cur_time);
    int m = std::max(no, yes);
    cout << idx << ":no=" << no << ":yes=" << yes << ":" << cur_time << endl;
    return m;
}

int main()
{
    int cur_time = 1;
    int t = get_profit(0,  cur_time);
    cout << t << endl;
}
