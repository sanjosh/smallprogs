/*

get max string compression after deleting upto k characters

https://leetcode.com/problems/string-compression-ii/

any k can be deleted 

samples
1. all same (aaaaa)
2. all different (abcdef)
3. diff frequencies (a3

what reduces length ?
1. single char = reduces 1 in length
2. repeated char = can reduce 2 in length

what to delete
1. prefer merger : if char of length 2 divides same char => leads to merger
2. prefer lowest frequency : 
3. do not delete partial if contiguous (all or nothing)

merging can get tricky (interpolating)
1. a2b2a2b2a2 - if u have to delete 4, delete a or b ?
delete b since that gives a6
delete a will give a2b4

how to represent this abstraction :

what operation needs to be easy
1. find same char if seen before
2. keep cumulative reduction in this path
3. keep remaining chars to delete

two array rep
[2, 2, 2, 2, 2]
[a, b, a, b, a]

find candidate locations

for each candidate location : store net reduction
1. if left and right can be merged, reduce length by it

but this means char deletions are not independent of each other
how to calculate if-then-else - 
this means new array should be passed to next iteration
need to keep stack of reduced arrays 

how to do it in single pass
detect previous occurence - you only need to detect one previous 

compressed array should indicate position instead of length : say cur pos or next pos (depending on merger)

while k > 0
if len[cur] <= k 
   if char[next] = char[prev]
       compressed[cur] = next
       merge[cur] = true
   else
       compressed[cur] = cur
       merge[cur] = false

do_final_sum
   sorted by compressed
   for each low to high
      if compressed[prev] == cur
       
reduce(n) = max (remove n, not_remove n ) + reduce(n-1)

like subset sum problem - find min sum

do special case for merger, otherwise regular linear algo

use if adjacent check while doing cumulative sum

int reduce(arr, index, cur_budget) -> cur_compress
{
    if len[index] <= k
        cur_budget -= k
        cur_compress -= 2
        cur_compress -= reduce(index + 1, cur_budget)
        if char[prev] == char[next] 
           new_compress = cur_compress - 2
           new_compress -= reduce(index + 2, cur_budget)
        else
           new_compress = cur_compress
        return min(cur_compress, new_compress)
    else 
       return reduce(index + 1, cur_budget)
}

 */

#include <iostream>

using namespace std;

int n = 5;
int len[] = {2, 3, 2, 3, 2};
int charat[] = {'a', 'b', 'a', 'b', 'a'};

// is double-counting happening when eliminating two 'b' ? No

/**
 * return max compress
 *  zero if end 
 */
int reduce(int index, int cur_budget)
{
    int red = 0;
    int new_budget = cur_budget;
    if (index >= n) {
        return 0;
    }
    bool merge = false;
    if (len[index] <= cur_budget) {
        new_budget -= len[index];
        if ((index - 1 >= 0) && (index + 1 < n) && (charat[index - 1] == charat[index + 1])) {
            red =  4 + reduce(index + 2, new_budget);
            merge = true;
        } else  {
            red = 2 + reduce(index + 1, new_budget);
        }
    } 
    int without_red = reduce(index + 1, cur_budget); // can be removed but do not
    if (red > without_red) {
        cout << index << ";merge=" << merge << ";red=" << red << ";new_bud=" << new_budget << endl;
        return red;
    } else {
        cout << index << ";noremove=" << without_red << ";cur_bud=" << cur_budget << endl;
        return without_red;
    }
}

int main() {
    int k = reduce(0, 6);
    cout << k << endl;
}
