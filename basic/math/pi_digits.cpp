
#include <stdio.h>
int main()
{
    double f = (double)220000000000000000/7;
    printf("%100.4f\n", f);
    printf("%100.4g\n", f);
    printf("%100.4e\n", f);
    printf("%100.4a\n", f);
}
