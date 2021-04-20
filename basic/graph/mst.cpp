/*

Linear time Randomized algo  - karger, Tarjan
    Intuition
    Cycle property
    - for any cycle, heaviest edge does not appear in MST
    - find all cycles of graph and remove heaviest edge

    Cut Property
    - for any subset X of vertices, lightest edge with exactly one endpt in X belongs to MST

    Boruvka + Cycle property + randomization = Linear time with high probability

Deterministic 
O(mα(m, n) log α(m, n)) - Chazelle
Reverse Delete algo : delete edges from full graph
Kruskal : add edges to empty graph
Prim
Boruvka : parallel - http://en.wikipedia.org/wiki/Bor%C5%AFvka%27s_algorithm
*/

#include <iostream>
#include <map>
#include <stdlib.h>

using namespace std;

struct Edge
{
    int a;
    int b;
    bool used;

    Edge(int _a, int _b) : a(_a), b(_b) {used = false;}
};

typedef map<int, Edge> EdgeWt; // wt, edge
typedef map<int, bool> MST; // vertex, exist

MST mst;
EdgeWt edgeWt;

int main(int argc, char* argv[])
{
    int numVertices = 30;

    unsigned int seed = 101;
    srand(seed);

    for (int i = 0; i < (numVertices * (numVertices -1))/4; i++)
    {
        int a, b;
        a = rand_r(&seed) % numVertices;
        do
        {
            b = rand_r(&seed) % numVertices;
        } while (a==b);

        int wt = (rand_r(&seed) % 100) + 1;
        Edge e(a, b);
        edgeWt.insert(make_pair(wt, e));
    }

    EdgeWt::iterator iter;
    for (iter = edgeWt.begin(); iter != edgeWt.end(); ++iter)
    {
        bool a = (mst.find(iter->second.a) != mst.end());
        bool b = (mst.find(iter->second.b) != mst.end());

        if (a & b)
        {
            continue;
        }
        else
        {
            if (!a) mst.insert(make_pair(iter->second.a, true));
            if (!b) mst.insert(make_pair(iter->second.b, true));
            iter->second.used = true;
            if (mst.size() == numVertices) break;
        }
    } 

    for (iter = edgeWt.begin(); iter != edgeWt.end(); ++iter)
    {
        if (iter->second.used)
        {
            cout << "wt=" << iter->first << ":edge " << iter->second.a << " to " << iter->second.b << " used=" << iter->second.used << endl;
        }
    }

    MST::iterator mstIter;
    for (mstIter = mst.begin(); mstIter != mst.end(); ++mstIter)
    {   
        cout << mstIter->first << endl;
    }
}
