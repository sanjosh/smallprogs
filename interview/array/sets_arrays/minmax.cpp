
http://www.geeksforgeeks.org/maximum-and-minimum-in-an-array/

Write a C function to return minimum and maximum in an array. You program should make minimum number of comparisons.

First of all, how do we return multiple values from a C function? We can do it either using structures or pointers.

We have created a structure named pair (which contains min and max) to return multiple values.
struct pair
{
  int min;
  int max;
}; 

And the function declaration becomes: struct pair getMinMax(int arr[], int n) where arr[] is the array of size n whose minimum and maximum are needed.

METHOD 1 (Simple Linear Search)
Initialize values of min and max as minimum and maximum of the first two elements respectively. Starting from 3rd, compare each element with max and min, and change max and min accordingly (i.e., if the element is smaller than min then change min, else if the element is greater than max then change max, else ignore the element)
/* structure is used to return two values from minMax() */
#include<stdio.h>
struct pair
{
  int min;
  int max;
}; 
 
struct pair getMinMax(int arr[], int n)
{
  struct pair minmax;    
  int i;
   
  /*If there is only one element then return it as min and max both*/
  if (n == 1)
  {
     minmax.max = arr[0];
     minmax.min = arr[0];    
     return minmax;
  }   
 
  /* If there are more than one elements, then initialize min
      and max*/
  if (arr[0] > arr[1]) 
  {
      minmax.max = arr[0];
      minmax.min = arr[1];
  } 
  else
  {
      minmax.max = arr[1];
      minmax.min = arr[0];
  }   
 
  for (i = 2; i<n; i++)
  {
    if (arr[i] >  minmax.max)     
      minmax.max = arr[i];
   
    else if (arr[i] <  minmax.min)     
      minmax.min = arr[i];
  }
   
  return minmax;
}
 
/* Driver program to test above function */
int main()
{
  int arr[] = {1000, 11, 445, 1, 330, 3000};
  int arr_size = 6;
  struct pair minmax = getMinMax (arr, arr_size);
  printf("\nMinimum element is %d", minmax.min);
  printf("\nMaximum element is %d", minmax.max);
  getchar();
} 

Time Complexity: O(n)

In this method, total number of comparisons is 1 + 2(n-2) in worst case and 1 + n – 2 in best case.
In the above implementation, worst case occurs when elements are sorted in descending order and best case occurs when elements are sorted in ascending order.



METHOD 2 (Tournament Method)
Divide the array into two parts and compare the maximums and minimums of the the two parts to get the maximum and the minimum of the the whole array.

Pair MaxMin(array, array_size)
   if array_size = 1
      return element as both max and min
   else if arry_size = 2
      one comparison to determine max and min
      return that pair
   else    /* array_size  > 2 */
      recur for max and min of left half
      recur for max and min of right half
      one comparison determines true max of the two candidates
      one comparison determines true min of the two candidates
      return the pair of max and min

Implementation
/* structure is used to return two values from minMax() */
#include<stdio.h>
struct pair
{
  int min;
  int max;
}; 
 
struct pair getMinMax(int arr[], int low, int high)
{
  struct pair minmax, mml, mmr;      
  int mid;
   
  /* If there is only on element */
  if (low == high)
  {
     minmax.max = arr[low];
     minmax.min = arr[low];    
     return minmax;
  }   
   
  /* If there are two elements */
  if (high == low + 1)
  { 
     if (arr[low] > arr[high]) 
     {
        minmax.max = arr[low];
        minmax.min = arr[high];
     } 
     else
     {
        minmax.max = arr[high];
        minmax.min = arr[low];
     } 
     return minmax;
  }
   
  /* If there are more than 2 elements */
  mid = (low + high)/2; 
  mml = getMinMax(arr, low, mid);
  mmr = getMinMax(arr, mid+1, high); 
   
  /* compare minimums of two parts*/
  if (mml.min < mmr.min)
    minmax.min = mml.min;
  else
    minmax.min = mmr.min;    
 
  /* compare maximums of two parts*/
  if (mml.max > mmr.max)
    minmax.max = mml.max;
  else
    minmax.max = mmr.max;    
  
  return minmax;
}
 
/* Driver program to test above function */
int main()
{
  int arr[] = {1000, 11, 445, 1, 330, 3000};
  int arr_size = 6;
  struct pair minmax = getMinMax(arr, 0, arr_size-1);
  printf("\nMinimum element is %d", minmax.min);
  printf("\nMaximum element is %d", minmax.max);
  getchar();
}

Time Complexity: O(n)
Total number of comparisons: let number of comparisons be T(n). T(n) can be written as follows:
Algorithmic Paradigm: Divide and Conquer

             
  T(n) = T(floor(n/2)) + T(ceil(n/2)) + 2  
  T(2) = 1
  T(1) = 0

If n is a power of 2, then we can write T(n) as:

   T(n) = 2T(n/2) + 2 

After solving above recursion, we get

  T(n)  = 3/2n -2 

Thus, the approach does 3/2n -2 comparisons if n is a power of 2. And it does more than 3/2n -2 comparisons if n is not a power of 2.



METHOD 3 (Compare in Pairs)
If n is odd then initialize min and max as first element.
If n is even then initialize min and max as minimum and maximum of the first two elements respectively.
For rest of the elements, pick them in pairs and compare their
maximum and minimum with max and min respectively.
#include<stdio.h>
 
/* structure is used to return two values from minMax() */
struct pair
{
  int min;
  int max;
}; 
 
struct pair getMinMax(int arr[], int n)
{
  struct pair minmax;    
  int i; 
 
  /* If array has even number of elements then
    initialize the first two elements as minimum and
    maximum */
  if (n%2 == 0)
  {        
    if (arr[0] > arr[1])    
    {
      minmax.max = arr[0];
      minmax.min = arr[1];
    } 
    else
    {
      minmax.min = arr[0];
      minmax.max = arr[1];
    }
    i = 2;  /* set the startung index for loop */
  } 
 
   /* If array has odd number of elements then
    initialize the first element as minimum and
    maximum */
  else
  {
    minmax.min = arr[0];
    minmax.max = arr[0];
    i = 1;  /* set the startung index for loop */
  }
   
  /* In the while loop, pick elements in pair and
     compare the pair with max and min so far */   
  while (i < n-1) 
  {         
    if (arr[i] > arr[i+1])         
    {
      if(arr[i] > minmax.max)       
        minmax.max = arr[i];
      if(arr[i+1] < minmax.min)         
        minmax.min = arr[i+1];       
    }
    else        
    {
      if (arr[i+1] > minmax.max)       
        minmax.max = arr[i+1];
      if (arr[i] < minmax.min)         
        minmax.min = arr[i];       
    }       
    i += 2; /* Increment the index by 2 as two
               elements are processed in loop */
  }           
 
  return minmax;
}   
 
/* Driver program to test above function */
int main()
{
  int arr[] = {1000, 11, 445, 1, 330, 3000};
  int arr_size = 6;
  struct pair minmax = getMinMax (arr, arr_size);
  printf("\nMinimum element is %d", minmax.min);
  printf("\nMaximum element is %d", minmax.max);
  getchar();
}

Time Complexity: O(n)

Total number of comparisons: Different for even and odd n, see below:

       If n is odd:    3*(n-1)/2  
       If n is even:   1 Initial comparison for initializing min and max, 
                           and 3(n-2)/2 comparisons for rest of the elements  
                      =  1 + 3*(n-2)/2 = 3n/2 -2

Second and third approaches make equal number of comparisons when n is a power of 2.

In general, method 3 seems to be the best.
