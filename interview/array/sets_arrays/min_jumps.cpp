/*

http://www.geeksforgeeks.org/minimum-number-of-jumps-to-reach-end-of-a-given-array/

TODO

Vinisha Vyasa Stackoverflow
*/

#include <stdio.h>
#include <stdlib.h>

int minJumpsUpdated(int arr[], int n)
{
  int *jumps = (int*)malloc(n * sizeof(int));  // jumps[n-1] will hold the result
  int i =1, j = 0;

  jumps[0] = 0;
  for (i = 1; i < n; ) { 

    // if i is out of range of arr[j], then increment j
    if (arr[j] + j < i && j < i) {

      printf("incre j= %d + 1\n", j);
      j++;

    	// else if i is within range of arr[j], 
    	//   jumps for ith element would be jumps[j]+1
    } else if (arr[j] + j >= i && j < i) {

      jumps[i] = jumps[j] + 1;
      printf("setting jumps[%d] to jumps[%d] + 1\n", i, j);
      i++;

    } else {
      printf("solution does not exist");
      return -1;
    }
  }

  printf("jumps: ");
  for (i = 0; i < n; i++) {
    printf("%d, ", jumps[i]);
  }
  return jumps[n - 1];
}

int main(int argc, char* argv[])
{
    int arr[] = {4, 4, 1, 1, 1, 4, 1, 1, 1};
    int n = sizeof(arr)/sizeof(arr[0]);

    int x = minJumpsUpdated(arr, n);
    
}
