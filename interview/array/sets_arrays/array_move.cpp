
/*
WAP to modify the array such that arr[I] = arr[arr[I]].
Do this in place i.e. with out using additional memory.

example : 
if  : a = {2,3,1,0}
o/p : a = {1,0,3,2} 

(x + y*size)/size = y    provided x and y is less than z.
(x + y*size)%size = x    provided x and y is less than z.

http://www.careercup.com/question?id=4909367207919616
*/

TODO NOT WORKING IF MORE THAN ONE ELEM OUT OF PLACE

#include <stdio.h>

void relocate(int *arr,int size) 
{
    for(int i=0;i<size;i++) 
    {
        if (arr[i] != i)
        {
            for(int i=0;i<size;i++) 
            {
                arr[i] += (arr[arr[i]] % size)*size; // x -> y
            }

            for(int i=0;i<size;i++) 
            {
                arr[i] /= size;
                printf("%d ", arr[i]);
            }
            printf("\n");                    
        }                
    }            
    for(int i=0;i<size;i++) 
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main(int argc, char* argv[])
{
    int arr[] = {2, 3, 4, 0, 1};

    relocate(arr, 5);
}
