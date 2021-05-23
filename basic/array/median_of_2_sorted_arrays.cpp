
/*
http://www.geeksforgeeks.org/median-of-two-sorted-arrays/

if A[n] < B[0]
    median =  n+m/2;    
if B[m] < A[0]
    median =  n+m/2;    
*/


#include <stdio.h>
 
int median(int [], int); /* to get median of a sorted array */
 
/* This function returns median of ar1[] and ar2[].
   Assumptions in this function:
   Both ar1[] and ar2[] are sorted arrays
   Both have n elements */
int getMedian(int ar1[], int ar2[], int n)
{
    int m1; /* For median of ar1 */
    int m2; /* For median of ar2 */
 
    /* return -1  for invalid input */
    if (n <= 0)
        return -1;
 
    if (n == 1)
        return (ar1[0] + ar2[0])/2;
 
    if (n == 2)
        return (std::max(ar1[0], ar2[0]) + std::min(ar1[1], ar2[1])) / 2;
 
    m1 = median(ar1, n); /* get the median of the first array */
    m2 = median(ar2, n); /* get the median of the second array */
 
    /* If medians are equal then return either m1 or m2 */
    if (m1 == m2)
        return m1;
 
     /* if m1 < m2 then median must exist in ar1[m1....] and ar2[....m2] */
    if (m1 < m2)
    {
        if (n % 2 == 0)
            return getMedian(ar1 + n/2 - 1, ar2, n - n/2 +1);
        else
            return getMedian(ar1 + n/2, ar2, n - n/2);
    }
 
    /* if m1 > m2 then median must exist in ar1[....m1] and ar2[m2...] */
    else
    {
        if (n % 2 == 0)
            return getMedian(ar2 + n/2 - 1, ar1, n - n/2 + 1);
        else
            return getMedian(ar2 + n/2, ar1, n - n/2);
    }
}
 
/* Function to get median of a sorted array */
int median(int arr[], int n)
{
    if (n%2 == 0)
        return (arr[n/2] + arr[n/2-1])/2;
    else
        return arr[n/2];
}
 
/* Driver program to test above function */
int main()
{
    int ar1[] = {1, 2, 3, 6};
    int ar2[] = {4, 6, 8, 10};
    int n1 = sizeof(ar1)/sizeof(ar1[0]);
    int n2 = sizeof(ar2)/sizeof(ar2[0]);
    if (n1 == n2)
      printf("Median is %d", getMedian(ar1, ar2, n1));
    else
     printf("Doesn't work for arrays of unequal size");
 
    getchar();
    return 0;
}
 
