
/*
print all strings of len k formed from n char
*/

#include <stdio.h>
#include <string.h>
#include <string.h>

char str[] = "ab";

#define MAXLEN 4

int generate(char a[], int pos)
{
    if (pos == MAXLEN)
    {
        printf("str=%s\n", a);
        return 0;
    }

    char now[MAXLEN];

    if (pos) strncpy(now, a, pos);

    for (int i = 0; i < strlen(str); i++)
    {
        now[pos] = str[i];
        generate(now, pos + 1);
    }
}

int main()
{
    char now[MAXLEN];
    memset(now, '\0', MAXLEN);
    generate(now, 0);
}

