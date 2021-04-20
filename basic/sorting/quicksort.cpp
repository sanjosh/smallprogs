
/* This function takes last element as pivot, places the pivot element at its
   correct position in sorted array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right of pivot */
int partition (int arr[], int l, int h)
{
    int x = arr[h];
    int i = (l - 1);
 
    for (int j = l; j <= h- 1; j++)
    {
        if (arr[j] <= x)
        {
            i++;
            swap (&arr[i], &arr[j]);
        }
    }
    swap (&arr[i + 1], &arr[h]);
    return (i + 1);
}
 
/* A[] --> Array to be sorted, l  --> Starting index, h  --> Ending index */
void quickSort(int A[], int l, int h)
{
    if (l < h)
    {       
        int p = partition(A, l, h); /* Partitioning index */
        quickSort(A, l, p - 1); 
        quickSort(A, p + 1, h);
    }
}

http://www.geeksforgeeks.org/iterative-quick-sort/

On DLL
http://www.geeksforgeeks.org/quicksort-for-linked-list/


ON SLL
http://www.geeksforgeeks.org/quicksort-on-singly-linked-list/
