
# Steps

* write examples
* smallest base case
* identify decomposition into smaller parts
* how to combine
* what is intrinsic optimal criterion
* write all cases to handle [ 0, 1, element equality, max length, max element ]
* write psuedo-code
* write code

# solving

* identify loop invariant or permutation invariant
* sort
* hash
* use modulo prime - use number theoretic props
* reduction to canonical form: x->x^2, linear, 2d, fourier, wavelet
* use swap, XOR or bit op
* exploit limited range of input values (van emde boas)
* augmented data structure (fenwick)
* auxiliary data structure (stack, queue, RMQ, segment tree, heap, fully sorted tree)
* bound the solution
* use symmetry 
* change radix
* keep multiple ptrs into input

## advanced

* primal-dual
* approximation algo
* randomized

## transform 

1. finding submatrix : use cumulative sums to transform it into 1-dim problem

## reverse the problem

1. next greater element : instead of putting "next element" in stack , keep stack of "previous" whose "nge" this element is
2. min jump : instead of marking till what point to jump, find if previous slot can jump to current

# ladder of solutions

2. does local choice work ? then greedy 
2. divide and conquer ? can combine ?
3. if not, find recurrence 
3. optimal substructure ? dynamic programming
4. nothing possible : use backtracking

# dynamic programming

1. recursion - start from maxElem and then reduce down, instead of maxElem = 1 and increase
1. return 1 on reaching leaf node, to indicate valid solution

# backtracking or recursive solutions

1. beware of infinite loops - use visitedSet, use visitedPath, use ranking to move in right direction
2. leaf condition
3. bounds checks

# complexity

go line-by-line

consider string length

if recursion branches K ways, then time is (K^n), where n is height of tree
example
1. knights tour - 8^n where n = height of tree which is 64 positions 
2. subset sum - n.(2^n) where n = height of tree, and n = time to sum a subset

backtracking
1. time to generate next move
2. number satisfying constrains

# misc

https://en.wikipedia.org/wiki/Bird%E2%80%93Meertens_formalism
