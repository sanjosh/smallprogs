/*

https://stackoverflow.com/questions/64921085/count-number-of-teams-javascript

https://leetcode.com/problems/count-number-of-teams/

----
Approach 1

take each element as mid

number of triples per elem = Number of lesser to left * number of greater to right

sum over all elements

relation is not transitive - NumLess[i] and NumLess[i-1]

this needs sorted tree 
insert in order of [1..n]
during every insert, should count numLeft, numRight

https://www.geeksforgeeks.org/find-number-of-triplets-in-array-such-that-aiajak-and-ijk/

----

organize all elements in ascending order

topological sorting

pick triples - number of subtrees of depth 3

----


every inversion prevents formation of triple with every element before & after

C(n, 3) - C(n-2, 2) * number of inversions 

----

longest increasing subsequence

keeping trie

for 1, 3, 2, 5, 4

[1]

[3, 4]
[3, 5]
[2, 4]
[2, 5]

[1, 2, 5]
[1, 2, 4]
[1, 3, 5]
[1, 3, 4]

at each elem, keep count of predecessors

for each element
   insert into all queues with last < elem and size <=2
   start new queue

*/

int getAscendingList(
