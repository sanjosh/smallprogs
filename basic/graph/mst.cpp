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
#include <set>
#include <stdlib.h>

using namespace std;

struct Edge
{
    int a;
    int b;
    int wt;

    explicit Edge(int _a, int _b, int w) : a(_a), b(_b), wt(w) {}
};

auto comp = [](Edge& a, Edge& b) { return a.wt < b.wt; };

set<Edge, decltype(comp)> edgeWt; // wt, edge
typedef set<int> MST; // vertex, exist

MST mst;

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
        Edge e(a, b, wt);
        edgeWt.insert(e);
    }

    for (auto iter : edgeWt) 
    {
        bool a = (mst.find(iter.a) != mst.end());
        bool b = (mst.find(iter.b) != mst.end());

        if (a & b)
        {
            continue;
        }
        else
        {
            cout << "using edge " << iter.a << "," << iter.b << ", " << iter.wt << endl;
            if (!a) mst.insert(iter.a);
            if (!b) mst.insert(iter.b);
            if (mst.size() == numVertices) break;
        }
    } 

    for (auto iter : mst)
    {   
        cout << iter << endl;
    }
}
