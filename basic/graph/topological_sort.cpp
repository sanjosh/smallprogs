
/*

while (any v with no incoming vertex)
{
    add vertex to topo list
    delete outgoing edges from v
}

in adj matrix representation
while (find vertex with column sum = 0)
{
    add vertex v to topo list
    delete all entries in that row = v
    (these are candidates to narrow next search)
    maintain index on indegree
}
print topo list

in edge rep
vector<set>
    
*/
