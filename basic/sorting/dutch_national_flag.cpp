
/*
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
*/

#include <iostream>
using namespace std;

int swap(int& one, int& two) {
    one = one xor two;
    two = one xor two;
    one = one xor two;
    return 0;
}

int sort012(int arr[], int arr_size) {

    int lo = 0;
    int hi = arr_size - 1;
    int mid = 0;

        while (arr[hi] == 2) {
            hi --;
        }
        while (arr[lo] == 0) {
            lo ++;
        }
        mid = lo;

    while (mid <= hi) {
        if (arr[mid] == 0) {
            swap(arr[lo], arr[mid]);
            cout << "loswap: " << lo << "," << mid << endl;
            lo ++;
        }
        else if (arr[mid] == 2) {
            swap(arr[hi], arr[mid]);
            cout << "hiswap: " << hi << "," << mid << endl;
            hi --;
        }
        mid ++;
    }
    return 0;
}

int main() {
    int a[] = {0, 2, 0, 2, 1, 2};
    int len = sizeof(a)/sizeof(a[0]);
    sort012(a, len);
    for (int i = 0; i < len; i++)
        cout << a[i] << ",";
    cout << endl;
}

