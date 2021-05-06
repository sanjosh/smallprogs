

/*

number of BST with N nodes

C_n+1 = Sum (Ci.C_n-i) over all i=0,n
*/

#include <set>
#include <vector>
#include <iostream>

using namespace std;

int countme(const std::vector<int>& a)
{
    int count = 0;

    if (a.size() == 0) return 1;
    else if (a.size() == 1) return 1;
    else if (a.size() == 2) return 2;

    for (auto iter = a.begin(); iter != a.end(); iter ++)
    {
        std::vector<int> left;
        if (iter != a.begin()) {
            left.assign(a.begin(), iter - 1);
        }
        std::vector<int> right;
        right.assign(iter + 1, a.end());
        int le = countme(left);
        int ri = countme(right);
        count += le * ri;
    }
    return count;
}

int main()
{
    std::vector<int> v{1, 2, 3, 4};
    cout << countme(v) << endl;
}
