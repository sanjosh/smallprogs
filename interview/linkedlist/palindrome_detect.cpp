/*
Given a linked list. You have to determine whether or not it is a palindrome in order O(n) time without using auxiliary space.

SOLUTION:

find length of list - O(n)
split list in the middle - O(n)
reverse second list O(n/2)
compare the two node by node O(n/2)

http://www.geeksforgeeks.org/function-to-check-if-a-singly-linked-list-is-palindrome/

also use recursion
compare last with first
move first
pop stack
compare 2nd last with second


*/

