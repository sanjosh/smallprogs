#include <iostream>
#include <stdlib.h>
#include <stdint.h>
using namespace std;

/* 
 * Number of distinct pairs for which x^2 + y^2 <= n
 * is same as Formula for Gauss circle problem 
 * First few sequences sequence A000328        
 * which is Number of points of norm <= n^2 in square lattice. 
 *  http://oeis.org/A000328
 */

int main(int argc, char* argv[])
{
    int r = atoi(argv[1]);
    int n = r*r;

    int64_t sum = 0;
    
    int64_t index = 0;
    int64_t term1 = 0;
    int64_t term2 = 0;
    do
    {
        term1 = n/((index << 2) + 1);
        term2 = n/((index << 2) + 3);
        if (!term1) 
        {
            break;
        }
        sum += (term1 - term2);
        index ++;
    } while (1);

    cout << "Number of ways to represent N=" << n << " as sum of squares is="  << 1 + 4*sum << ":loop ends=" << index << endl;
}
