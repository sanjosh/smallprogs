#include <iostream>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
using namespace std;

#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))
 

int levenshtein(char *s1, char *s2) {
    unsigned int x, y, s1len, s2len;
    s1len = strlen(s1);
    s2len = strlen(s2);
    unsigned int matrix[s2len+1][s1len+1];
    matrix[0][0] = 0;
    for (x = 1; x <= s2len; x++)
        matrix[x][0] = matrix[x-1][0] + 1;
        // first col is 0 1 2 3 4 5
    for (y = 1; y <= s1len; y++)
        matrix[0][y] = matrix[0][y-1] + 1;
        // first row is 0 1 2 3 4 5
    for (x = 1; x <= s2len; x++)
        for (y = 1; y <= s1len; y++)
        {
            matrix[x][y] = MIN3(
                matrix[x-1][y] + 1,  // top cell
                matrix[x][y-1] + 1,  // left cell
                matrix[x-1][y-1] + (s1[y-1] == s2[x-1] ? 0 : 1));
        }

/* 
    left cell -  deletion
    top cell -  insertion
*/

    for (x = 1; x <= s2len; x++)
    {
        for (y = 1; y <= s1len; y++)
        {
            cout << matrix[x][y] << " " ;
        }
        cout << endl;
    }

 
    return(matrix[s2len][s1len]);
}

int main(int argc, char* argv[])
{
    if (argc != 3) exit(1);
    int d = levenshtein(argv[1], argv[2]);
    cout << d << endl;
}
