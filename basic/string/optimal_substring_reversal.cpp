/*
TODO

Optimal substring reversal
http://www.geeksforgeeks.org/directi-interview-questions/

Question 1 (Optimal substring reversal):
    You are given a string S. 

    Each character of S is either ‘a’, or ‘b’. 

    You wish to reverse exactly one sub-string of S such that the new string is lexicographically smaller 
    than all the other strings that you can get by reversing exactly one sub-string.

    For example, given ‘abab’, you may choose to reverse the substring ‘ab’ that starts from index 2 (0-based). 
    This gives you the string ‘abba’. 

    But, if you choose the reverse the substring ‘ba’ starting from index 1, you will get ‘aabb’. 

    There is no way of getting a smaller string, hence reversing the substring in the range [1, 2] is optimal.

*/
