    /*
    L(i) = 1 + max [L(j)] for all j < i and arr[j] < arr[i]

1) O(n^2) soln Dynamic Programming
2) n.log(n) soln using pred[i] and max[i]
3) longest common subseq (set , its sorted version)

Related to Young's tableau - Schensted

http://www.geeksforgeeks.org/dynamic-programming-set-3-longest-increasing-subsequence/

Let us discuss Longest Increasing Subsequence (LIS) problem as an example problem that can be solved using Dynamic Programming.
The longest Increasing Subsequence (LIS) problem is to find the length of the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. For example, length of LIS for { 10, 22, 9, 33, 21, 50, 41, 60, 80 } is 6 and LIS is {10, 22, 33, 50, 60, 80}.

Optimal Substructure:
Let arr[0..n-1] be the input array and L(i) be the length of the LIS till index i such that arr[i] is part of LIS and arr[i] is the last element in LIS, then L(i) can be recursively written as.
L(i) = { 1 + Max ( L(j) ) } where j < i and arr[j] < arr[i] and if there is no such j then L(i) = 1
To get LIS of a given array, we need to return max(L(i)) where 0 < i < n
So the LIS problem has optimal substructure property as the main problem can be solved using solutions to subproblems.

Overlapping Subproblems:
Following is simple recursive implementation of the LIS problem. The implementation simply follows the recursive structure mentioned above. The value of lis ending with every element is returned using max_ending_here. The overall lis is returned using pointer to a variable max.
*/

/* A Naive recursive implementation of LIS problem */

#include<stdio.h>
#include<stdlib.h>
 
/* To make use of recursive calls, this function must return two things:
   1) Length of LIS ending with element arr[n-1]. We use max_ending_here
      for this purpose
   2) Overall maximum as the LIS may end with an element before arr[n-1]
      max_ref is used this purpose.
The value of LIS of full array of size n is stored in *max_ref which is our final result
*/

int _lis( int arr[], int n, int *max_ref)
{
    /* Base case */
    if(n == 1)
        return 1;
 
    int res, max_ending_here = 1; // length of LIS ending with arr[n-1]
 
    /* Recursively get all LIS ending with arr[0], arr[1] ... ar[n-2]. If
       arr[i-1] is smaller than arr[n-1], and max ending with arr[n-1] needs
       to be updated, then update it */
    for(int i = 1; i < n; i++)
    {
        res = _lis(arr, i, max_ref);
        if (arr[i-1] < arr[n-1] && res + 1 > max_ending_here)
            max_ending_here = res + 1;
    }
 
    // Compare max_ending_here with the overall max. And update the
    // overall max if needed
    if (*max_ref < max_ending_here)
       *max_ref = max_ending_here;
 
    // Return length of LIS ending with arr[n-1]
    return max_ending_here;
}
 
// The wrapper function for _lis()
int lis(int arr[], int n)
{
    // The max variable holds the result
    int max = 1;
 
    // The function _lis() stores its result in max
    _lis( arr, n, &max );
 
    // returns max
    return max;
}
 
/* Driver program to test above function */
int main()
{
    int arr[] = { 10, 22, 9, 33, 21, 50, 41, 60 };
    int n = sizeof(arr)/sizeof(arr[0]);
    printf("Length of LIS is %d\n",  lis( arr, n ));
    getchar();
    return 0;
}

/*
Considering the above implementation, following is recursion tree for an array of size 4. lis(n) gives us the length of LIS for arr[].

    
                     lis(4)           
                 /       |      \
         lis(3)      lis(2)    lis(1)  
        /     \        /         
  lis(2)  lis(1)   lis(1) 
  /    
lis(1) 

We can see that there are many subproblems which are solved again and again. So this problem has Overlapping Substructure property and recomputation of same subproblems can be avoided by either using Memoization or Tabulation. Following is a tabluated implementation for the LIS problem.

*/
/* Dynamic Programming implementation of LIS problem */
#include<stdio.h>
#include<stdlib.h>
 
/* lis() returns the length of the longest increasing subsequence in
    arr[] of size n */
int lis( int arr[], int n )
{
   int *lis, i, j, max = 0;
   lis = (int*) malloc ( sizeof( int ) * n );
 
   /* Initialize LIS values for all indexes */
   for ( i = 0; i < n; i++ )
      lis[i] = 1;
    
   /* Compute optimized LIS values in bottom up manner */
   for ( i = 1; i < n; i++ )
      for ( j = 0; j < i; j++ )
         if ( arr[i] > arr[j] && lis[i] < lis[j] + 1)
            lis[i] = lis[j] + 1;
    
   /* Pick maximum of all LIS values */
   for ( i = 0; i < n; i++ )
      if ( max < lis[i] )
         max = lis[i];
 
   /* Free memory to avoid memory leak */
   free( lis );
 
   return max;
}
 
/* Driver program to test above function */
int main()
{
  int arr[] = { 10, 22, 9, 33, 21, 50, 41, 60 };
  int n = sizeof(arr)/sizeof(arr[0]);
  printf("Length of LIS is %d\n", lis( arr, n ) );
 
  getchar();
  return 0;
}

/*
Note that the time complexity of the above Dynamic Programmig (DP) solution is O(n^2) and there is a O(nLogn) solution for the LIS problem (see this). We have not discussed the nLogn solution here as the purpose of this post is to explain Dynamic Programmig with a simple example. 

The algorithm outlined below solves the longest increasing subsequence problem efficiently with arrays and binary searching. It processes the sequence elements in order, maintaining the longest increasing subsequence found so far. Denote the sequence values as X[0], X[1], etc. Then, after processing X[i], the algorithm will have stored values in two arrays:

    M[j] — stores the index k of the smallest value X[k] such that there is an increasing subsequence of length j ending at X[k] on the range k ≤ i (note we have j ≤ k ≤ i here, because j represents the length of the increasing subsequence, and k represents the index of its termination. Obviously, we can never have an increasing subsequence of length 13 ending at index 11. k ≤ i by definition).
    P[k] — stores the index of the predecessor of X[k] in the longest increasing subsequence ending at X[k].

In addition the algorithm stores a variable L representing the length of the longest increasing subsequence found so far. Because the algorithm below uses zero-based numbering, for clarity we pad M with M[0], which goes unused so that M[j] corresponds to a subsequence of length j. A real implementation can skip M[0] and adjust the indices accordingly.

Note that, at any point in the algorithm, the sequence

    X[M[1]], X[M[2]], ..., X[M[L]]

is nondecreasing. For, if there is an increasing subsequence of length i ending at X[M[i]], then there is also a subsequence of length i-1 ending at a smaller value: namely the one ending at X[P[M[i]]]. Thus, we may do binary searches in this sequence in logarithmic time.

The algorithm, then, proceeds as follows:

 P = array of length N
 M = array of length N + 1

 L = 0
 for i in range 0 to N-1:
   // Binary search for the largest positive j ≤ L
   // such that X[M[j]] < X[i]
   lo = 1
   hi = L
   while lo ≤ hi:
     mid = (lo+hi)/2
     if X[M[mid]] < X[i]:
       lo = mid+1
     else:
       hi = mid-1

   // After searching, lo is 1 greater than the
   // length of the longest prefix of X[i]
   newL = lo

   // The predecessor of X[i] is the last index of 
   // the subsequence of length newL-1
   P[i] = M[newL-1]

   if newL > L:
     // If we found a subsequence longer than any we've
     // found yet, update M and L
     M[newL] = i
     L = newL
   else if X[i] < X[M[newL]]:
     // If we found a smaller last value for the
     // subsequence of length newL, only update M
     M[newL] = i

 // Reconstruct the longest increasing subsequence
 S = array of length L
 k = M[L]
 for i in range L-1 to 0:
   S[i] = X[k]
   k = P[k]

 return S

Because the algorithm performs a single binary search per sequence element, its total time can be expressed using Big O notation as O(n log n). Fredman (1975) discusses a variant of this algorithm, which he credits to Donald Knuth; in the variant that he studies, the algorithm tests whether each value X[i] can be used to extend the current longest increasing sequence, in constant time, prior to doing the binary search. With this modification, the algorithm uses at most n log2 n − n log2log2 n + O(n) comparisons in the worst case, which is optimal for a comparison-based algorithm up to the constant factor in the O(n) term.[5]:w

=================
*/

/*
http://www.geeksforgeeks.org/dynamic-programming-set-14-variations-of-lis/

We have discussed Dynamic Programming solution for Longest Increasing Subsequence problem in this post and a O(nLogn) solution in this post. 
Following are commonly asked variations of the standard LIS problem.

1. Building Bridges: Consider a 2-D map with a horizontal river passing through its center. 
There are n cities on the southern bank with x-coordinates a(1) … a(n) 
and n cities on the northern bank with x-coordinates b(1) … b(n). 

You want to connect as many north-south pairs of cities as possible with bridges such that no two bridges cross. 
When connecting cities, you can only connect city i on the northern bank to city i on the southern bank.

8     1     4     3     5     2     6     7  
<---- Cities on the other bank of river---->
--------------------------------------------
  <--------------- River--------------->
--------------------------------------------
1     2     3     4     5     6     7     8
<------- Cities on one bank of river------->

Source: Dynamic Programming Practice Problems. The link also has well explained solution for the problem.


2. Maximum Sum Increasing Subsequence: Given an array of n positive integers. Write a program to find the maximum sum subsequence of the given array such that the intgers in the subsequence are sorted in increasing order. For example, if input is {1, 101, 2, 3, 100, 4, 5}, then output should be {1, 2, 3, 100}. The solution to this problem has been published here.


3. The Longest Chain You are given pairs of numbers. In a pair, the first number is smaller with respect to the second number. Suppose you have two sets (a, b) and (c, d), the second set can follow the first set if b < c. So you can form a long chain in the similar fashion. Find the longest chain which can be formed. The solution to this problem has been published here.

4. Box Stacking You are given a set of n types of rectangular 3-D boxes, where the i^th box has height h(i), width w(i) and depth d(i) (all real numbers). You want to create a stack of boxes which is as tall as possible, but you can only stack a box on top of another box if the dimensions of the 2-D base of the lower box are each strictly larger than those of the 2-D base of the higher box. Of course, you can rotate a box so that any side functions as its base. It is also allowable to use multiple instances of the same type of box.
Source: Dynamic Programming Practice Problems. The link also has well explained solution for the problem.

*/



