randomized 
deterministic

http://en.wikipedia.org/wiki/Median_of_medians

TODO

find kth smallest -order statistic 

QuickSelect by Hoare
http://en.wikipedia.org/wiki/Quickselect
Chooses pivot but only sorts one side

quickselect(L,k)
    {
    pick x in L
    partition L into L1<x, L2=x, L3>x
    if (k <= length(L1))
        return quickselect(L1,k)
    else if (k > length(L1)+length(L2))
        return quickselect(L3,k-length(L1)-length(L2))
    else return x
    }

http://www.ics.uci.edu/~eppstein/161/960125.html


===============

find median - Blum Tarjan median of medians O(n)

http://www.ics.uci.edu/~eppstein/161/960130.html


    Line up elements in groups of five (this number 5 is not important, it could be e.g. 7 without changing the algorithm much). Call each group S[i], with i ranging from 1 to n/5.
    Find the median of each group. (Call this x[i]). This takes 6 comparisons per group, so 6n/5 total (it is linear time because we are taking medians of very small subsets).
    Find the median of the x[i], using a recursive call to the algorithm. If we write a recurrence in which T(n) is the time to run the algorithm on a list of n items, this step takes time T(n/5). Let M be this median of medians.
    Use M to partition the input and call the algorithm recursively on one of the partitions, just like in quickselect.


select(L,k)
{
    if (L has 10 or fewer elements)
    {
        sort L
        return the element in the kth position
    }
}

this is O(n) algo

    partition L into subsets S[i] of five elements each
        (there will be n/5 subsets total).

    for (i = 1 to n/5) do
        x[i] = select(S[i],3) (//each set has comparisons=7; total=7.n/5)

    M = select({x[i]}, n/10)  (//comparison=n/5)

    partition L into L1<M, L2=M, L3>M (//comparisons = n-1)

    // comparison = atmost 7n/10 elem
    if (k <= length(L1))
        return select(L1,k)
    else if (k > length(L1)+length(L2))
        return select(L3,k-length(L1)-length(L2))
    else return M
    }

===========

int quickSelect(int items[], int first, int last, int k) {
    int pivot = partition(items, first, last);
    if (k < pivot-first+1) { //boundary was wrong
        return quickSelect(items, first, pivot, k);
    } else if (k > pivot-first+1) {//boundary was wrong
        return quickSelect(items, pivot+1, last, k-pivot);
    } else {
        return items[pivot];//index was wrong
    }
}
