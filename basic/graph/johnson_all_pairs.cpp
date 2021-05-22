
/*
http://www.geeksforgeeks.org/interesting-shortest-path-questions-set-1/

adding a number to all edges : changes shortest path
multiplying number to all edges : does not

Johnson all pairs for sparse graph

Reweight edges

 The idea of Johnson’s algorithm is to assign a weight to every vertex. 
 Let the weight assigned to vertex u be h[u]. 
 We reweight edges using vertex weights. 
 For example, for an edge (u, v) of weight w(u, v), the new weight becomes w(u, v) + h[u] – h[v]. 
 The great thing about this reweighting is, all set of paths between any two vertices are increased by same amount and all negative weights become non-negative. 
 Consider any path between two vertices s and t, weight of every path is increased by h[s] – h[t], all h[] values of vertices on path from s to t cancel each other.

How do we calculate h[] values? 
Bellman-Ford algorithm is used for this purpose. 

Following is the complete algorithm. 
A new vertex is added to the graph and connected to all existing vertices. 
The shortest distance values from new vertex to all existing vertices are h[] values.

1) Let the given graph be G. Add a new vertex s to the graph, add edges from new vertex to all vertices of G. Let the modified graph be G’.

2) Run Bellman-Ford algorithm on G’ with s as source. Let the distances calculated by Bellman-Ford be h[0], h[1], .. h[V-1]. If we find a negative weight cycle, then return. Note that the negative weight cycle cannot be created by new vertex s as there is no edge to s. All edges are from s.

3) Reweight the edges of original graph. For each edge (u, v), assign the new weight as “original weight + h[u] – h[v]“.

4) Remove the added vertex s and run Dijkstra’s algorithm for every vertex.

Bellman Ford is O(VE) : run 1 time
Djikstra is O(V.LogV) : run V times

So total time = O(V^2.logV + VE)
For complete graph = O(V^2)

*/
