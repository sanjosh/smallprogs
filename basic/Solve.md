
Steps
* write examples
* smallest base case
* identify decomposition into smaller parts
* all cases to handle [ 0, 1, element equality, max length, max element ]
* write psuedo-code
* write code

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

advanced
* primal-dual
* approximation algo
* randomized

ladder 
1. transform the problem
2. does local choice work ? then greedy 
2. divide and conquer ?
3. if not, find recurrence 
3. optimal substructure - dynamic programming
4. nothing possible : use backtracking

if recursion branches K ways - time is (K^n), where n is height of tree
example
1. knights tour - 8^n where n = height of tree which is 64 positions 
2. subset sum - n.(2^n) where n = height of tree, and n = time to sum a subset
