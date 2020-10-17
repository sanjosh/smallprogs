#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include <iostream>

/*

average = n.logn
worst = n^2 - bad pivot


function quicksort(array)
    less, equal, greater := three empty arrays
    if length(array) > 1  
        pivot := select any element of array
        for each x in array
            if x < pivot then add x to less
            if x = pivot then add x to equal
            if x > pivot then add x to greater
        quicksort(less)
        quicksort(greater)
        array := concatenate(less, equal, greater)

1<=n<=1000
-1000<=x<= 1000 , x ∈ ar
There are no duplicate numbers.

Sample Input

7
5 8 1 3 7 9 2

Sample Output
2 3
1 2 3
7 8 9
1 2 3 5 7 8 9 

*/

using namespace std;

#include <list>

void printArr2(const list<int>& elems)
{
    list<int>::const_iterator iter;
    for (iter = elems.begin(); iter != elems.end(); ++iter)
    {
        printf("%d ", *iter);
    }
    printf("\n");
}


int newsort(list<int>& elems, int level)
{
    list<int> less; 
    list<int> eq; 
    list<int> gt; 

    int elemsize = elems.size();
    if (elems.size() > 1)
    {
        list<int>::iterator iter = elems.begin();
        int pivot = *iter;
        eq.push_back(pivot);

        iter ++;
        for (; iter != elems.end(); ++iter)
        {   
            if (*iter < pivot) less.push_back(*iter);
            else if (*iter == pivot) eq.push_back(*iter);
            else if (*iter > pivot) gt.push_back(*iter);
            else assert("what" == 0);
        }

        newsort(less, level+1);
        newsort(gt, level+1);

        elems = less;
        elems.insert(elems.end(), eq.begin(), eq.end());
        elems.insert(elems.end(), gt.begin(), gt.end());

        printArr2(elems);
    }
    assert(elemsize == elems.size());
    return 0;
}


int main(int argc, char* argv[])
{
    int NUM = 0;
    list<int> elems;

    scanf("%d", &NUM);

    for (int i = 0; i < NUM; i++)
    {
        int val;
        cin >> val;
        elems.push_back(val);
    }

    newsort(elems, 1);
}
