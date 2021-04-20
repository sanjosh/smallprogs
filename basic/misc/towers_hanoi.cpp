#include <stdio.h>
#include <stdlib.h>

void towers_of_hanio(int n, char from, char to, char temp)
{
    if(n > 0)
    {
        towers_of_hanio(n-1, from, temp, to);
        printf("\nMove disk %d from %c to %c\n", n, from, to);
        towers_of_hanio(n-1, temp, to, from);
    }
} 

int main(int argc, char* argv[])
{
    int n = 10;
    if (argc > 1) n = atoi(argv[1]);
    towers_of_hanio(n,'L','R','C');
}

