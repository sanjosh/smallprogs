#include <iostream>
#include <stdlib.h>
#include <stdint.h>
using namespace std;

/* 
 * Formula for Gauss circle problem 
 * First few sequences sequence A000328        
 * which is Number of points of norm <= n^2 in square lattice. 
 *  http://oeis.org/A000328
 */

int main(int argc, char* argv[])
{
    int r = atoi(argv[1]);

    int r_sq = r*r;

    int64_t sum = 0;
    
    int64_t index = 0;
    int64_t term1 = 0;
    int64_t term2 = 0;
    do
    {
        term1 = r_sq/((index << 2) + 1);
        term2 = r_sq/((index << 2) + 3);
        sum += (term1 - term2);
        index ++;
    } while (term1 > 0);

    cout << "Number of ways to represent N=" << r << " as sum of squares is="  << 1 + 4*sum << ":loop ends=" << index << endl;
}
