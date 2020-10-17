
/* Cormen Rivest 8.2 */

/* aassume each int in A is in range 0..k*/
/* if k=O(n), sort runs in Theta(n) time */

// non-comparison sorts do not require n.log(n) time

CountingSort(int A[], int B[], int k)
{
    int C[n]

    for i = 0 to k
        C[i] = 0

    for j = 1 to A.length
        C[A[j]] = C[A[j]] + 1 // C[j] = number of elem eq to j

    for i = 1 to k
        C[i] = C[i] + C[i-1]  // C[j] has all elem less than or eq j
    
    for j = A.length downto 1
        B[C[A[j]]] = A[j] <-- C[A[j]] is final pos of A[j]
        C[A[j]] --; // required if there are A[j] elem are not distinct
}
