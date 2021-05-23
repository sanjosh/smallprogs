
/*
http://www.geeksforgeeks.org/given-an-array-arr-find-the-maximum-j-i-such-that-arrj-arri/

FInd max (j-i) such that arr[j] > arr[i]

Method 2 (Efficient)
    To solve this problem, we need to get two optimum indexes of arr[]: left index i and right index j. 

    For an element arr[i], we do not need to consider arr[i] for left index if there is an element smaller than arr[i] 
    on left side of arr[i]. 

    Similarly, if there is a greater element on right side of arr[j] then we do not need to consider this j for right index. 

    So we construct two auxiliary arrays LMin[] and RMax[] such that 
    LMin[i] holds the smallest element on left side of arr[i] including arr[i], 
    and RMax[j] holds the greatest element on right side of arr[j] including arr[j]. 

    After constructing these two auxiliary arrays, we traverse both of these arrays from left to right. 

    While traversing LMin[] and RMa[] if we see that LMin[i] is greater than RMax[j], then 
    we must move ahead in LMin[] (or do i++) because all elements on left of LMin[i] are greater than or equal to LMin[i]. 

    Otherwise we must move ahead in RMax[j] to look for a greater j – i value.

    Thanks to celicom for suggesting the algorithm for this method.
    */
#include <stdio.h>
#include <stdlib.h>
     
/* Utility Functions to get max and minimum of two integers */
int max(int x, int y)
{
    return x > y? x : y;
}
 
int min(int x, int y)
{
    return x < y? x : y;
}
 
/* For a given array arr[], returns the maximum j – i such that
 *     arr[j] > arr[i] */
int maxIndexDiff(int arr[], int n)
{
    int maxDiff;
    int i, j;
             
    int *LMin = (int *)malloc(sizeof(int)*n);
    int *RMax = (int *)malloc(sizeof(int)*n);
                     
                       /* Construct LMin[] such that LMin[i] stores the minimum value
                        *        from (arr[0], arr[1], ... arr[i]) */
    LMin[0] = arr[0];
    for (i = 1; i < n; ++i)
    {            
        LMin[i] = min(arr[i], LMin[i-1]);
        printf("%d ", LMin[i]);
    }            
    printf("\n");
                             
    /* Construct RMax[] such that RMax[j] stores the maximum value
                                 *        from (arr[j], arr[j+1], ..arr[n-1]) */
    RMax[n-1] = arr[n-1];
    for (j = n-2; j >= 0; --j)
    {
        RMax[j] = max(arr[j], RMax[j+1]);
    }            
    for (j = 0; j < n; j++)
    {
        printf("%d ", RMax[j]);
    }
    printf("\n");
                                     
    /* Traverse both arrays from left to right to find optimum j - i
       *         This process is similar to merge() of MergeSort */
    i = 0, j = 0, maxDiff = -1;
    while (j < n && i < n)
    {
        if (LMin[i] < RMax[j])
        {
            maxDiff = max(maxDiff, j-i);
            printf("maxdiff=%d index=%d:%d\n", maxDiff, LMin[i], RMax[j]);
            j = j + 1;
        }
        else
            i = i+1;
    }
                                    
    return maxDiff;
}
 

/* Driver program to test above functions */
int main()
{
    int arr[] = {9, 2, 3, 4, 25, 6, 7, 1, 18, 0};
    int n = sizeof(arr)/sizeof(arr[0]);
    int maxDiff = maxIndexDiff(arr, n);
    printf("%d\n", maxDiff);
    return 0;
}
