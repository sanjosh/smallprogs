
TODO

total rec = Fn - 1 
Left subtree has F(n-2) - 1
Right subtree has F(n-1) - 1

First  : 5 
Second : 2 or 8
Third  : 1,3 or 6,10

might have better locality of reference ? better for sequential media ? for records always at head of tape ?

Compared to binary search, Fibonacci search examines locations whose addresses have lower dispersion. Therefore, when the elements being searched have non-uniform access memory storage (i.e., the time needed to access a storage location varies depending on the location previously accessed), the Fibonacci search has an advantage over binary search in slightly reducing the average time needed to access a storage location. The typical example of non-uniform access storage is that of a magnetic tape, where the time to access a particular element is proportional to its distance from the element currently under the tape’s head. 


Fn = Fn-1 + Fn-2

http://en.wikipedia.org/wiki/Fibonacci_search_technique


when the elements being searched have non-uniform access memory storage (i.e., the time needed to access a storage location varies depending on the location previously accessed), the Fibonacci search has an advantage over binary search in slightly reducing the average time needed to access a storage location.

also helpful in searching for max of unimodal function


/ Fibonacci search, search A[1],A[2],...,A[N]
// Here N+1 must be a Fibonacci number, F[m+1]
int fibSearch(int y) { // y = A[x], 0 < x < F[m+1]
   int mid = F[m]; // F[m] is partway from 0 to F[m+1]
   int p   = F[m-1] = F[m] - F[m-1]
   int q   = F[m-2] = 2*F[m-1} - F[m]
   for (;;) {
      System.out.println("mid:" + mid + ", p:" + p + ",q:" + q);
      if (y == A[mid) return mid;
      else if (y < A[mid) {
         if (q == 0) return -(mid - 1);
         mid = mid - q;
         int temp = p;
         p = q;
         q = temp - q;
      }
      else if (y > A[mid]) {
         if (p == 1) return -mid;
         mid = mid + q;
         p = p - q;
         q = q - p;
      }
   }
}
