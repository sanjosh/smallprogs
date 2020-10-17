
http://www.careercup.com/question?id=5717488440442880

http://www.geeksforgeeks.org/median-of-stream-of-integers-running-integers/

FInd median of running set of numbers

We need to maintain 1 max heap and 1 min heap. Max heap will contain lower half of the numbers and min the upper half. Whenever, a new number comes:

1) if its less than root of max heap, it is inserted into max heap.
2) if its higher than root of min heap, it is inserted into min heap.
3) after insertion if the size difference of two heaps is greater than 1, the root of the larger heap is transferred to the other heap to balance their size.

At any point, the median will be:
1) (root of max heap + root of min heap) / 2 if size of both heap are equal.
2) root of larger heap otherwise.

