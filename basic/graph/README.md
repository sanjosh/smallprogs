
# Solving

1. visited array
2. BFS
3. DFS O(V+E)
4. earliest discovered time as in disc[vertex]=++counter; 
5. earliest in subtree low[vertex] = min(low[vertex and its adjacents]) like union-find

path exploration variables should be on stack

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
