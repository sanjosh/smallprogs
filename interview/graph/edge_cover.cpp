
Edge cover is poly time but vertex cover is NP-hard

Edge cover is special case of set cover - where each subset has 2 elements -but set cover is NP-complete

Edge cover can be found by finding max matching and extending it greedily

Perfect matching (1-factor) matches all vertices of graph

Gallai : min Edge cover + Matching number =  | V |

Edmonds (blossom) matching algo for general graphs - poly time
Contract every blossom(odd 2k+1 cycle) into a vertex

Matching polytope - Integer programming
matrix is 0/1 - permutation matrix

Edmonds algo like Boruvka's MST : both start with individual vertices and merge them

===========

from vertex A
    find shortest path to all other vertices V
may not give best matching (odd/even length path)

need vertex disjoint paths

bipartite matching:
do a graph partition - using Laplacian=D-A  (NP-hard)
find paths between pairs of vertices on both sides

find paths between any pair of vertices

need to find V/2 edges

for vertices ordered by increasing degree
    find unused edge to another vertex
    color the edge 
    color both this and the other vertex as taken

vertex disjoing odd len paths

each phase requires examining edges O(e)
how many phases - O(v) - adds atleast 2 vertices


Fork Fulkerson is O(v.e)
Edmonds  : O(n^4) - with O(n^3) per stage
Micali Vazirani : in phase i, find paths of length (2i+1)

===========

M=0, n = |V|
For v = 1 to n do
    find augmenting path wrt M starting at v
    if success, we got a path P
    M = M + P
end for
return M

===========

    // if number of vertices is odd, one always left out

    // find edge which does not have any vertex common with M
    // may not find
    // M = M + e

    // need all odd length vertex disjoint paths
    // find 2 edges which each have one endpt common with current M
    // M = M + e1 + e2
    if Adj(v) in Unmatched and Adj(u) in Unmatched
    add those 2 edges as path 
    add those 2 vertices 

=============


