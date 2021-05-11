/*


https://www.techiedelight.com/count-distinct-elements-every-sub-array-size-k-array/

https://stackoverflow.com/questions/39787455/is-it-possible-to-query-number-of-distinct-integers-in-a-range-in-olg-n

two types of problems
1. find distinct in arbitrary range (l, k)
2. find distinct in consecutive subarrays of len k

-----------

second problem like countMin
Keep frequency count per element and update on window change

-----------

first problem

Approach 1. 
segment tree (fractional cascading)
next occurence array

https://www.geeksforgeeks.org/queries-number-distinct-elements-subarray/


*/
