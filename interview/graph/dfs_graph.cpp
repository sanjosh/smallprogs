
DFS (graph) = preorder(tree)

//:w http://www.ics.uci.edu/~eppstein/161/960215.html
TODO

preorder(node v)
{
    visit(v);
    for each child w of v
        preorder(w);
}

dfs(vertex v)
{
    visit(v);
    for each neighbor w of v
        if w is unvisited
        {
        dfs(w);
        add edge vw to tree T
        }
}

//===================

    bfs(G)
    {
    list L = empty
    tree T = empty
    choose a starting vertex x
    search(x)
    while(L nonempty)
        remove edge (v,w) from start of L
        if w not yet visited
        {
        add (v,w) to T
        search(w)
        }
    }

    dfs(G)
    {
    list L = empty
    tree T = empty
    choose a starting vertex x
    search(x)
    while(L nonempty)
        remove edge (v,w) from end of L
        if w not yet visited
        {
        add (v,w) to T
        search(w)
        }
    }

    search(vertex v)
    {
    visit(v);
    for each edge (v,w)
        add edge (v,w) to end of L
    }

Both of these search algorithms now keep a list of edges to explore; the only difference between the two is that, 
while both algorithms adds items to the end of L, 
BFS removes them from the beginning, which results in maintaining the list as a queue, 
while DFS removes them from the end, maintaining the list as a stack.
