/*


http://stackoverflow.com/questions/6420467/find-any-one-of-multiple-possible-repeated-integers-in-a-list

Use floyd cycle finding

Facebook question: You have an array of N integers, all between 1 and N-1.  Using O(1) extra memory, O(N) time, and without modifying the array identify a repeated integer.  Note that there may be multiple such integers.


*/

#include <iostream>
using namespace std;


int swap(int& a, int& b)
{
    int tmp =a;
    a = b;
    b = tmp;
    return 0;
}

int main(int argc, char* argv[])
{
    int A[] = { 2, 4, 6, 5, 0, 2, 1};
    int n = sizeof(A)/sizeof(A[0]);

    for (int i =0; i < n; i++)
    {
        while (A[A[i]] != A[i])
        {
            cout << "swap:" << i << ":" << A[i] << " with " << A[A[i]] << endl;
            swap(A[i], A[A[i]]);
        }
    }

    for (int i = 0; i < n; i++)
    {
        cout <<  A[i];
        if (A[i] != i)
            cout << " here" ;
        cout << endl;
    }
}

http://www.geeksforgeeks.org/find-duplicates-in-on-time-and-constant-extra-space/


Given an array of n elements which contains elements from 0 to n-1, with any of these numbers appearing any number of times. Find these repeating numbers in O(n) and using only constant memory space.

For example, let n be 7 and array be {1, 2, 3, 1, 3, 6, 6}, the answer should be 1, 3 and 6.

This problem is an extended version of following problem.

Find the two repeating elements in a given array

Method 1 and Method 2 of the above link are not applicable as the question says O(n) time complexity and O(1) constant space. Also, Method 3 and Method 4 cannot be applied here because there can be more than 2 repeating elements in this problem. Method 5 can be extended to work for this problem. Below is the solution that is similar to the Method 5.

Algorithm:

traverse the list for i= 0 to n-1 elements
{
  check for sign of A[abs(A[i])] ;
  if positive then
     make it negative by   A[abs(A[i])]=-A[abs(A[i])];
  else  // i.e., A[abs(A[i])] is negative
     this   element (ith element of list) is a repetition
}

Implementation:
#include <stdio.h>
#include <stdlib.h>
 
void printRepeating(int arr[], int size)
{
  int i;
  printf("The repeating elements are: \n");
  for (i = 0; i < size; i++)
  {
    if (arr[abs(arr[i])] >= 0)
      arr[abs(arr[i])] = -arr[abs(arr[i])];
    else
      printf(" %d ", abs(arr[i]));
  }
}
 
int main()
{
  int arr[] = {1, 2, 3, 1, 3, 6, 6};
  int arr_size = sizeof(arr)/sizeof(arr[0]);
  printRepeating(arr, arr_size);
  getchar();
  return 0;
}

Note: The above program doesn’t handle 0 case (If 0 is present in array). The program can be easily modified to handle that also. It is not handled to keep the code simple.

Output:
The repeating elements are:
1 3 6

Time Complexity: O(n)
Auxiliary Space: O(1)

http://www.geeksforgeeks.org/find-the-two-repeating-elements-in-a-given-array/

Method 3 (Make two equations)
Let the numbers which are being repeated are X and Y. We make two equations for X and Y and the simple task left is to solve the two equations.
We know the sum of integers from 1 to n is n(n+1)/2 and product is n!. We calculate the sum of input array, when this sum is subtracted from n(n+1)/2, we get X + Y because X and Y are the two numbers missing from set [1..n]. Similarly calculate product of input array, when this product is divided from n!, we get X*Y. Given sum and product of X and Y, we can find easily out X and Y.

Let summation of all numbers in array be S and product be P

X + Y = S – n(n+1)/2
XY = P/n!

Using above two equations, we can find out X and Y. For array = 4 2 4 5 2 3 1, we get S = 21 and P as 960.

X + Y = 21 – 15 = 6

XY = 960/5! = 8

X – Y = sqrt((X+Y)^2 – 4*XY) = sqrt(4) = 2

Using below two equations, we easily get X = (6 + 2)/2 and Y = (6-2)/2
X + Y = 6
X – Y = 2

Thanks to geek4u for suggesting this method. As pointed by Beginer , there can be addition and multiplication overflow problem with this approach.
The methods 3 and 4 use all useful information given in the question :)
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
 
/* function to get factorial of n */
int fact(int n);
 
void printRepeating(int arr[], int size)
{
  int S = 0;  /* S is for sum of elements in arr[] */
  int P = 1;  /* P is for product of elements in arr[] */ 
  int x,  y;   /* x and y are two repeating elements */
  int D;      /* D is for difference of x and y, i.e., x-y*/
  int n = size - 2,  i;
 
  /* Calculate Sum and Product of all elements in arr[] */
  for(i = 0; i < size; i++)
  {
    S = S + arr[i];
    P = P*arr[i];
  }       
   
  S = S - n*(n+1)/2;  /* S is x + y now */
  P = P/fact(n);         /* P is x*y now */
   
  D = sqrt(S*S - 4*P); /* D is x - y now */
   
  x = (D + S)/2;
  y = (S - D)/2;
   
  printf("The two Repeating elements are %d & %d", x, y);
}    
 
int fact(int n)
{
   return (n == 0)? 1 : n*fact(n-1);
}   
 
int main()
{
  int arr[] = {4, 2, 4, 5, 2, 3, 1};
  int arr_size = sizeof(arr)/sizeof(arr[0]); 
  printRepeating(arr, arr_size);
  getchar();
  return 0;
}

Time Complexity: O(n)
Auxiliary Space: O(1)



Method 4 (Use XOR)
Thanks to neophyte for suggesting this method.
The approach used here is similar to method 2 of this post.
Let the repeating numbers be X and Y, if we xor all the elements in the array and all integers from 1 to n, then the result is X xor Y.
The 1’s in binary representation of X xor Y is corresponding to the different bits between X and Y. Suppose that the kth bit of X xor Y is 1, we can xor all the elements in the array and all integers from 1 to n, whose kth bits are 1. The result will be one of X and Y.
void printRepeating(int arr[], int size)
{
  int xor = arr[0]; /* Will hold xor of all elements */
  int set_bit_no;  /* Will have only single set bit of xor */
  int i;
  int n = size - 2;
  int x = 0, y = 0;
   
  /* Get the xor of all elements in arr[] and {1, 2 .. n} */
  for(i = 1; i < size; i++)
    xor ^= arr[i]; 
  for(i = 1; i <= n; i++)
    xor ^= i;  
 
  /* Get the rightmost set bit in set_bit_no */
  set_bit_no = xor & ~(xor-1);
 
  /* Now divide elements in two sets by comparing rightmost set
   bit of xor with bit at same position in each element. */
  for(i = 0; i < size; i++)
  {
    if(arr[i] & set_bit_no)
      x = x ^ arr[i]; /*XOR of first set in arr[] */
    else
      y = y ^ arr[i]; /*XOR of second set in arr[] */
  }
  for(i = 1; i <= n; i++)
  {
    if(i & set_bit_no)
      x = x ^ i; /*XOR of first set in arr[] and {1, 2, ...n }*/
    else
      y = y ^ i; /*XOR of second set in arr[] and {1, 2, ...n } */
  }
   
  printf("\n The two repeating elements are %d & %d ", x, y);
}    
 
 
int main()
{
  int arr[] = {4, 2, 4, 5, 2, 3, 1};
  int arr_size = sizeof(arr)/sizeof(arr[0]); 
  printRepeating(arr, arr_size);
  getchar();
  return 0;
}


