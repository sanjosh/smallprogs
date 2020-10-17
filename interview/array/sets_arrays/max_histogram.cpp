
/*
Karumanchi chap 5 : prob 24
*/

#include <iostream>

#include <vector>
#include <stack>
#include <stdlib.h>
using namespace std;

#define NUM 12
/*
typedef vector<int> Histogram;

Histogram hist;


    struct StackElem
    {
        int height;
        int index;
        StackElem(int h, int l) : height(h), index(l) {}
        StackElem() {}
    };

int FindArea()
{
    int maxarea = hist[0];

    vector<StackElem> mys;
    StackElem first(hist[0], 0);
    mys.push_back(first);

    for (int i = 1; i < NUM; i++)
    {
        int index = mys.size() - 1;

        while ((index >= 0) && ((i == NUM) || (mys[index].height > hist[i])))
        {
            int left = mys[index].index;
            int curarea = (i - left - 1) * mys[index].height;
            if (curarea > maxarea) 
            {
                cout << "from " << left << " to " << i << " ht= " << mys[index].height << endl;
                maxarea = curarea;
            }
            --index;
        }
        StackElem newelem(hist[i], i);
        mys.push_back(newelem);
    }
    return maxarea;
}

int main(int argc, char* argv[])
{
    unsigned int seed;
    //srand(seed);
    
    for (int i = 0; i < NUM-1; i++)
    {
        int num;
        hist.push_back(num = rand_r(&seed) % NUM);
        //hist.push_back(num = i);
        cout <<  num << " ";
    }
    hist.push_back(0);
    cout << endl;

    int max = FindArea();
    cout << max << endl;
}

*/

struct StackItem
{
    int data;
    int index;
};

int FindArea(int A[], int n)
{
    int i, maxArea = -1, top = -1, left, currentArea;
    
    struct StackItem* S = (StackItem*)malloc(sizeof(StackItem) * n);

    for (i = 0; i <=n; i++)
    {
        // pop all prev numbers which are > current
        // i==n is end condition
        while (top >= 0 && (i==n || S[top].data > A[i]))
        {
            if (top > 0)
                left = S[top-1].index; // count from prev small elem
            else
                left = -1;// because this is min elem in all array

            currentArea = (i-left -1) * (S[top].data);
            cout << "top=" << top << ":area=" << currentArea << ":left=" << left << ":cur=" << i-1 << ":height=" << S[top].data;
            if (currentArea > maxArea) 
            {
                maxArea = currentArea;
                cout << " IS MAX";
            }
            cout << endl;
            --top;
        }
        if (i < n)
        {
            ++top;
            S[top].data = A[i];
            S[top].index = i;
            cout << "pushed top=" << top << ":height=" << A[i] << ":index=" << i << endl;
        }
    }
    return maxArea;
}

int main(int argc, char* argv[])
{
    int A[NUM] = {4,9,3,2,4,4,3,3,4,3,1};
    for (int i =0; i < NUM; i++)    
        cout << A[i] << " ";    
    cout << endl;

    int max = FindArea(A, NUM);
    cout << max << endl;
}
