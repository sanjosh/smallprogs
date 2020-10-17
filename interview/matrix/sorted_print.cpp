
/*

Matrix is in row and column increasing order

   1  2  4   7
   2  3  5   8
   2  4  6  10
   3  6  8  12

Print each elem from matrix in sorted order

SOLUTION:

Keep a MinHeap containing the (row,col) positions with smallest elem, one for each row and column
Keep popping elements and print them
For each element popped, insert the next column and next row if a smaller element for that 
row and column doesn't already exist

FUNC()
{
    MinHeap.insert(row0, col0)
    
    while (MinHeap is not empty)
    {
        CurrentSmallest = MinHeap.pop()
        print the element at this position
    
        NextCol = NextColumn(CurrentSmallest)
        if (no smaller row, col than NextCol exists in MinHeap)
            MinHeap.push(NextCol)
    
        NextRow = NextRow(CurrentSmallest)
        if (no smaller row, col than NextRow exists in MinHeap)
            MinHeap.push(NextRow)
    }
}

*/

#include <list>
#include <iostream>
#include <cassert>

using namespace std; 

typedef unsigned int Index;
typedef unsigned int Elem;

struct Pos
{
    Index x;
    Index y;

    Pos(Index argx, Index argy) : x(argx), y(argy) {}

    Pos nextColumn()
    {
       return Pos(x, y+1);
    }
    Pos nextRow()
    {
       return Pos(x+1, y);
    }
};

#define ARRSIZE 4

struct Array
{
    Elem array[ARRSIZE][ARRSIZE];

    Array()
    {
        for (Index i = 0; i < ARRSIZE; i++)
            for (Index j = 0; j < ARRSIZE; j++)
                array[i][j] = (3*i) + (2*j); // dummy initialization
    }

    size_t size() { return ARRSIZE; }

    bool isValid(const Pos& p) 
    {
        return (p.x < ARRSIZE) && (p.y < ARRSIZE);
    }

    void print(ostream& ostr)
    {
        for (Index i = 0; i < ARRSIZE; i++)
        {
            for (Index j = 0; j < ARRSIZE; j++)
            {
                ostr << array[i][j] << " ";
            }
            cout << endl;
        }
    }

};

struct Frontier
{
    // Frontier is the moving set of positions out of which the next minimum is chosen

    Array& a; // array on which minheap created

    std::list<Pos> heap;
        // should really be a priority_queue<Pos> but that requires a comparison op, so keeping a list for now 
        // also need an index to determine if a smaller Pos exists for a particular row/col

    Frontier(Array& a_) : a(a_)
    {
        Pos cur(0, 0);
        push(cur);
    }

    size_t size()
    {
        return heap.size();
    }

    int pop(Pos& ret)
    {
        if (heap.size())
        {
            Pos first = heap.front();
            heap.pop_front();
            ret = first;
            return 0;
        }
        return -1;
    }

    void push(const Pos& newPos)
    {
        // insert such that heap remains sorted
        bool found = false;
        size_t newElem = a.array[newPos.x][newPos.y];

        list<Pos>::iterator iter;
        for (iter = heap.begin(); iter != heap.end(); ++ iter)
        {
            Index curRow = iter->x;
            Index curCol = iter->y;

            if (newElem < a.array[curRow][curCol]) 
            {
                found = true;
                heap.insert(iter, newPos);
                break;
            }
        }
        if (!found)
        {
            heap.insert(heap.end(), newPos);
        }
    }

    bool existsSameRowOrColumn(const Pos& newPos)
    {
        // this should use a bitmap in industrial-strength version
        bool found = false;

        list<Pos>::const_iterator iter;
        for (iter = heap.begin(); iter != heap.end(); ++ iter)
        {
            Index curRow = iter->x;
            Index curCol = iter->y;

            if ((curRow <= newPos.x) && (curCol <= newPos.y)) 
            {
                found = true;
                break;
            }
        }
        return found;
    }
};

int main()
{
    Array a;
    Frontier f(a);

    a.print(cout);

    Elem prevElem = 0;

    while (f.size())
    {   
        Pos cur(0, 0);

        int ret = f.pop(cur);

        if (ret != 0)
        {
            cerr << "some error" << endl;
            break;
        }
    
        Elem curElem = a.array[cur.x][cur.y];
        assert(curElem >= prevElem);

        cout << "pos=" << cur.x << ":" << cur.y << ":elem=" << curElem << endl;

        curElem = prevElem;

        Pos nc = cur.nextColumn();
        if ((a.isValid(nc)) && !f.existsSameRowOrColumn(nc))
        {
            f.push(nc);
        }

        Pos nr = cur.nextRow();
        if ((a.isValid(nr)) && !f.existsSameRowOrColumn(nr))
        {
            f.push(nr);
        }
    }
}

/*

http://ideone.com/nuFwoz

    #include <iostream>
    #include <queue>
    #include <vector>
    #include<iomanip>
    #include<climits>
    using namespace std;
    struct Node{
    int data;
    int i;
    int j;
    };
    class compare{
    public:
    bool operator ()(Node &l,Node &r){return l.data>r.data; }
    };
    void srtMat(int m[][4],vector<int> &v,int n)
    {
    priority_queue<Node,vector<Node>,compare> minHeap;
    for(int i=0;i<n;i++)
    {
    Node d;
    d.data=m[i][0];
    d.i=i;
    d.j=1;
    minHeap.push(d);
    }
     
    for(int i=0;i<n*n;i++)
    {
    Node d=minHeap.top(); minHeap.pop();
    v.push_back(d.data);
    if(d.j<n){d.data=m[d.i][d.j]; d.j++; }
    else d.data=INT_MAX;
    minHeap.push(d);
    }
     
    return;
    }
    int main() {
    int mat[4][4] = {{10, 20, 30, 40},
    {15, 25, 35, 45},
    {27, 29, 37, 48},
    {32, 33, 39, 50},
    };
    vector<int> v;
    srtMat(mat,v,4);
    for(unsigned int i=0;i<v.size();i++)
    cout<<v[i]<<" ";
    return 0;
    }
*/
