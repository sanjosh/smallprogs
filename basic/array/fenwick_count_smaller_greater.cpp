/*
https://www.geeksforgeeks.org/find-number-of-triplets-in-array-such-that-aiajak-and-ijk/
 */

#include <iostream>
#include <cassert>

using namespace std;

template <int NUM>
class Fenwick
{
    /*
     *    array looks like 1,2,1,4,1,2,1,8,
     */

    public:
    static constexpr int MAXN = NUM;

    private:
    int arr[MAXN + 1];

    // sentinel
    // add one more element; entry i=0 is unused because lsbit fails on 0
    inline int lsbit(int i) {
        return (i & -i);
    }

    public:
    
    Fenwick()
    {
        for (int i = 0; i <= MAXN; i++)
        {
            arr[i] = 0;
        }
    }

    /**
        add 1:1,2,4,8,
        add 2:2,4,8,
        add 3:3,4,8,
        add 4:4,8,
        add 5:5,6,8,
        add 6:6,8,
        add 7:7,8,
        add 8:8,
 
    */
    void add(int idx, int val)
    {
        idx = idx + 1; // adjust idx to ignore zero entry
        cout << "add " << idx << ":";
        for (; idx <= MAXN; idx += lsbit(idx))
        {
            cout << idx << ",";
            arr[idx] += val;
        }
        cout << endl;
    }

    /**
        range 1:1,
        range 2:2,
        range 3:3,2,
        range 4:4,
        range 5:5,4,
        range 6:6,4,
        range 7:7,6,4,
        range 8:8,
    */
    int range(int idx)
    {
        int sum = 0;
        idx = idx + 1; // adjust idx to ignore zero entry
        cout << "range " << idx << ":";
        for (; idx > 0; idx -= lsbit(idx))
        {
            cout << idx << ",";
            sum += arr[idx];
        }
        cout << endl;
        return sum;
    }

    void print()
    {
        for (int i = 1; i <= MAXN; i++)
        {
            cout << arr[i] << ",";
        }
        cout << endl;
    }
};

void print_arr(int arr[], int n)
{
    for (int i = 0; i < n; i ++)
    {
            cout << arr[i] << ",";
    }
    cout << endl;
}


int main()
{
    /*
    Fenwick<8> a;
    for (int i = 0; i < a.MAXN; i++)
        a.add(i, 1);
    for (int i = 0; i < a.MAXN; i++) {
        int r = a.range(i);
    }
    a.print();
    */
    
    int orig[] = { 1, 2, 7, 6, 5, 4, 3, 0};
    int n = 8;

    // to handle numbers beyond array size
    // size of fenwick should be MAX (1 + max number in array, size of array)
    //     std::max((int)a.size(), 1 + *std::max_element(a.begin(), a.end())

    // can handle duplicates 

    // to handle negatives, increment all by largest min

    // during insert or query, insert index = value of element

    {
        Fenwick<8> b;
        int smaller_right[n];
        for (int i = n - 1; i >= 0; i--) {
            // smaller than orig[i] and to the right
            // query all inserted before
            smaller_right[i] = b.range(orig[i] - 1);
            b.add(orig[i], 1);
            b.print();
        }
        print_arr(smaller_right, n);
    }

    {
        Fenwick<8> c;
        int greater_left[n];
        for (int i = 0; i < n; i++) {
            greater_left[i] = i - c.range(orig[i]);
            c.add(orig[i], 1);
        }
        print_arr(greater_left, n);
    }
}
