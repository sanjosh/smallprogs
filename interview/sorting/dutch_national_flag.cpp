
TODO
http://www.geeksforgeeks.org/sort-an-array-of-0s-1s-and-2s/

void sort012(int a[], int arr_size)
{
   int lo = 0;
   int hi = arr_size - 1;
   int mid = 0;
 
   while(mid <= hi)
   {
      while ((a[hi]==2) && hi >= mid)
         -–hi;
      if (hi < mid)
         break;

      switch(a[mid])
      {
         case 0:
           swap(&a[lo++], &a[mid++]);
           break;
         case 1:
           mid++;
           break;
         case 2:
           swap(&a[mid], &a[hi--]);
           break;
      }
   }
}
