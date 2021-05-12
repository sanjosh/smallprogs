/*


https://www.techiedelight.com/count-distinct-elements-every-sub-array-size-k-array/

https://stackoverflow.com/questions/39787455/is-it-possible-to-query-number-of-distinct-integers-in-a-range-in-olg-n

two types of problems
1. find distinct in arbitrary range (l, k)
2. find distinct in consecutive subarrays of len k

-----------


first problem

Approach 1. 
next occurence array

https://www.geeksforgeeks.org/queries-number-distinct-elements-subarray/

Fenwick tree - numDistinct

last_visit[i] holds the rightmost index of the number i

Mo's algorithm
https://codeforces.com/blog/entry/7383

---------
Approach 2 : segment tree

form a segment tree in which the nodes will store all the distinct elements in the range
https://www.geeksforgeeks.org/queries-for-number-of-distinct-elements-in-a-subarray-set-2/

-----------

second problem like countMin

Keep frequency count per element and update on window change

-----------
*/
