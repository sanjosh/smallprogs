#include <iostream>
using namespace std;
#include <stdlib.h>

#define ARRSZ(a) sizeof(a)/sizeof(a[0])

int main(int argc, char* argv[])
{
    int a[] = {2, 3, 5, 8, 13};
    int b[] = {4, 8, 12, 16};

    int na = ARRSZ(a);
    int nb = ARRSZ(b);

    int k = atoi(argv[1]);

    int i = na-1;
    int j = nb-1;

#define MAX 10000

    for (int x = na+nb-2; x > 0; x--)
    {
        int af = a[i] + b[x - i];
        int bf = a[i + 1] + b[x - (i+1)];

        i--;
    }

    cout << argv[1] << "th-sum is " << a[i] << ":" << b[j] << endl;
}
