
TODO

total rec = Fn - 1 
Left subtree has F(n-2) - 1
Right subtree has F(n-1) - 1

First  : 5 
Second : 2 or 8
Third  : 1,3 or 6,10

might have better locality of reference ? better for sequential media ? for records always at head of tape ?

Compared to binary search, Fibonacci search examines locations whose addresses have lower dispersion. Therefore, when the elements being searched have non-uniform access memory storage (i.e., the time needed to access a storage location varies depending on the location previously accessed), the Fibonacci search has an advantage over binary search in slightly reducing the average time needed to access a storage location. The typical example of non-uniform access storage is that of a magnetic tape, where the time to access a particular element is proportional to its distance from the element currently under the tape’s head. 



