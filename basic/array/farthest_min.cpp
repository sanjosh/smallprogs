
/* 

to find farthest min element on right

https://www.geeksforgeeks.org/find-the-farthest-smaller-number-in-the-right-side/?ref=rp

{7, 5, ..., 3, 8}
fm(7) = 3
fm(5) = 3

{7, 10, ..., 3, 8}
fm(7) = 3 => all elem after are  greater than 7
fm(10) = 8 

hence index(7, 3) intersects index(10, 8)

intersection occurs hence stack cannot be used

instead keep range information
     
min element in each range is stored

min_range(i to n) = min (min_range[i+1], a[i])

fm(i) = binary search (min_range from i+1 to n)

*/

void FarthestMin(int arr[], int num)
{
    
}
