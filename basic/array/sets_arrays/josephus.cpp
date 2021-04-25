
/*
http://www.geeksforgeeks.org/josephus-problem-set-1-a-on-solution/

https://www.geeksforgeeks.org/josephus-problem-using-bit-magic/?ref=rp

1. use recursion
josephus(n, k) = (josephus(n - 1, k) + k-1) % n + 1
  josephus(1, k) = 1

2. use array indicating dead/alive


*/

#include <iostream>
using namespace std;

int josephus(int n, int k)
{
    if (n == 1) {
        return 1;
    }
    int x = josephus(n - 1, k);
    int val = ((x + k - 1) % n) + 1;
    return val;
}


int main()
{
    int v = josephus(10, 3);
    cout << v << endl;
}
