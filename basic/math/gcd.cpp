#include <cstdlib>
#include <iostream>

using namespace std;

int gcd(int a, int b)
{
    int temp;
    while(b > 0)
    {
        temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

int main(int argc, char* argv[])
{
    cout << gcd(atoi(argv[1]), atoi(argv[2])) << endl;
}


