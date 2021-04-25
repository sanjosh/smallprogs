
/*

in sorted array, record 
1. increment between successive
2. number of repeated elements

say 2, 3, 3, 7, 16
then dist = 1, 4, 9
then repeat = 1, 2, 1, 1

in unsorted array, 
1. create dict of frequency of each

create histogram of highest bit set per number

to get count of distinct elements - hyperloglog

to find duplicates, use hits in bloom filter


*/

#include <array>
#include <vector>
#include <iostream>

using namespace std;

void histogram(std::vector<int32_t>& a)
{
    std::array<int32_t, 32> b;
    for (auto e : a) {
        start = 0x01;
        int idx = 0;
        while (start != 0x1000) {
            if (start & e) {
                b[idx] ++;
            }
            start = (start << 1);
            idx ++;
        }
    }
}

int main()
{
    array<int32_t, 5> ar = {1, 2, 3, 4, 5};
    std::vector<int32_t> v (std::begin(ar), std::end(ar));
    histogram(v);
}
