
# Solving

1. visited array
2. BFS
3. DFS O(V+E)
4. earliest discovered time as in disc[vertex]=++counter; 
5. earliest in subtree low[vertex] = min(low[vertex and its adjacents]) like union-find
7. path exploration variables should be on stack
8. transform to shortest path 
9. start with dist[start] = 0 and all others = INF; then dist[v] = dist[u] + edge(u, v)
6. for early path pruning, use BFS over DFS
10. to find multiple shortest paths in BFS, update the visitedSet after level is done
11. Bidirectional BFS

## diff

BFS vs Djikstra vs Dynamic programming

DP = recursive definition

BFS = Djikstra on unweighted graph

Djikstra : shortest path (s, t) also implies shortest (s, i) to every intermediate vertex i from s

Djikstra = BFS + priority queue + distance matrix

Djikstra is a DP

Djikstra has relaxation of distance (minimize to new value)

Djikstra stops if shortest path found

BFS visits nodes in order of depth, not distance


# BFS

1. vertices discovered in increasing order of distance from root
1. the shortest path tree is only useful if BFS was performed with x as the root of the search. 
1. BFS only gives the shortest path if the graph is unweighted.
1. if constraints in path, same node can be visited twice.   To simulate this add constraint to visited set hash (so same node visited twice) 
1. Add param to Node put in BFS queue, if path tracking info needed (priority queue or nodes visited in this path)

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

Kahn algo

Enqueue vertices with zero incoming degree into a (priority) queue Q;

```
while (Q is not empty) {
	node u = Q.dequeue();     // put node u into a topological sort list;
	for (all child nodes of vertex u) {
		indegree[child]--;          // remove this node u and all outgoing edges from this node;
		if (indegree[child] == 0)
			Q.enqueue(child);     // if such removal causes node child to have zero incoming degree, enqueue it in queue;
	}
}
```

https://leetcode.com/problems/largest-color-value-in-a-directed-graph/discuss/1220930/C%2B%2B%3A-DP-%2B-Topological-Sort-(Kahn's-Algorithm)-solution


Note: To detect cycle in graph using this algo, if at the end of topo sort, if any node has indegree > 0, there is a cycle present in the graph.

```
bool cyclePresent = false;
for (each node v in graph)
	if (indegree[v] != 0)
		cyclePresent = true;

bool cyclePresent = std::for_each(v.begin(), v.end(), [](Point& v) -> bool { return indegree[v] != 0; })
```

# number of components

union-find

use of rank

keep size of each component

# djikstra shortest path

for all j, distance(j) = INF
distance(start) = 0

add start to visitedSet

while visitedSet < all vertices
   next = nearest vertex not in visitedSet with shortest distance 
   add next to visitedSet
   for each adjacent of next
      if not visited and edge(adj, next) and distance(next) not INF
         distance(adj) = min(distance(adj), distance(next) + edge(adj, next))

O(V * V)

can be O(V.logV) with a heap

## augmented

1. custom comparator & add priority queue to get vertices in certain order
2. at each level, you can keep parent 
3. at each level, keep distance found to each node 
4. in constraint-based visiting, same vertex needs to be visited for each value of constraint.
   so visited set must be able to include same vertex multiple times.  use hash based on constraint

# all pairs shortest floyd warshall

O(V^3)
 
for each intermediate vertex (k)
   for each vertex pair (a, b)
      if dist(a, b) > dist(a, k) + dist(k, b)
         dist(a, b) = dist(a, k) + dist(k, b)

# bellman ford negative edges

1. process all pairs at dist=1
1. process all pairs at dist=2
1. process all pairs at dist=V

there can be max V edges in a path

O(V.E)

# johnson negative edges

 w(u, v) + h[u] – h[v]

