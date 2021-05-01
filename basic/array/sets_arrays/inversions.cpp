
/*
Count inversions using merge sort

http://www.geeksforgeeks.org/counting-inversions/

 Suppose we know the number of inversions in the left half and right half of the array (let be inv1 and inv2), 
 what kinds of inversions are not accounted for in Inv1 + Inv2? The answer is – the inversions we have to 
 count during the merge step. Therefore, to get number of inversions, we need to add number of inversions in 
 left subarray, right subarray and merge(). 

 https://www.geeksforgeeks.org/count-inversions-in-an-array-set-2-using-self-balancing-bst/

 https://www.geeksforgeeks.org/counting-inversions-using-set-in-c-stl/

 https://www.geeksforgeeks.org/count-inversions-array-set-3-using-bit/

*/

int merge(int[] arr, int[] left, int[] right) 
{
    int i = 0, j = 0, count = 0;
    while (i < left.length || j < right.length) 
    {
        if (i == left.length) {
            arr[i+j] = right[j];
            j++;
        } else if (j == right.length) {
            arr[i+j] = left[i];
            i++;
        } else if (left[i] <= right[j]) {
            arr[i+j] = left[i];
            i++;                
        } else {
            arr[i+j] = right[j];
            count += left.length-i;
            j++;
        }
    }
    return count;
}

int invCount(int[] arr) 
{
    if (arr.length < 2)
        return 0;

    int m = (arr.length + 1) / 2;
    int left[] = Arrays.copyOfRange(arr, 0, m);
    int right[] = Arrays.copyOfRange(arr, m, arr.length);

    return invCount(left) + invCount(right) + merge(arr, left, right);
}

