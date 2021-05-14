
# Solving

1. visited array
2. BFS
3. DFS O(V+E)
4. earliest discovered time as in disc[vertex]=++counter; 
5. earliest in subtree low[vertex] = min(low[vertex and its adjacents]) like union-find
6. for early path pruning, use BFS over DFS

path exploration variables should be on stack

# BFS

1. vertices discovered in increasing order of distance from root
1. the shortest path tree is only useful if BFS was performed with x as the root of the search. 
1. BFS only gives the shortest path if the graph is unweighted.

O(V+E) on adjacency list
O(V^2) on adjacency matrix

since (V x adjacentE = sum of edges = E), hence it is E

# DFS

The difference between the exit and entry times for v tells us how many descendents v has in the DFS tree. 

The clock gets incremented on each vertex entry and vertex exit, so half the time difference 
denotes the number of descendents of v

used by Tarjan strongly connected (lowestIndex and discoveryIndex array)

It partitions the edges of an undirected graph into exactly two classes: 
1. tree edges and 
2. back edges.  (edge is not processed but other vertex is discovered but not processed)

The tree edges discover new vertices, and are those encoded in the parent relation. 

Back edges are those whose other endpoint is an ancestor of the vertex being expanded,
so they point back into the tree.


(Skiena Algo design manual)

# strongly connected components Tarjan

detect back edge

Case1 (Tree Edge): 

If node v is not visited already, then after DFS of v is complete, 
then minimum of low[u] and low[v] will be updated to low[u].

low[u] = min(low[u], low[v]);

Case 2 (Back Edge): 

When child v is already visited, 
then minimum of low[u] and Disc[v] will be updated to low[u].

low[u] = min(low[u], disc[v]);

DFS O(V + E)

# strongly connected component kosaraju

DFS O(V + E)

all vertices must be visited in both
1. DFS 
2. DFS with edges reversed 



# euler cycle

in degree = out degree for every vertex
single strongly connected component


# matching

augmenting path : initial and final vertex not in matching

alternating path : edges belong alternately to matching

# topological sorting

BFS

for every edge, decrement indegree on every incoming edge

when indegree of vertex is zero, add to queue

pop from queue and add vertex to sorted list

(Skiena)


# shortest path

for all j, distance(j) = INF

update nearest distance to all vertices outside visited set

visitedSet

while count < all vertices
   next = nearest vertex in NotVisitedSet with shortest distance 
   add next to visitedSet
   for each adjacent of next
      distance(adj) = distance(next) + edge(next, adj)

O(V * V)

# all pairs shortest floyd warshall
 
for each intermediate vertex (k)
   for each vertex pair (a, b)
      if dist(a, b) > dist(a, k) + dist(k, b)
         dist(a, b) = dist(a, k) + dist(k, b)

# reweighting negative

johnson 

bellman ford

 w(u, v) + h[u] – h[v]
