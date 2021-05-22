#include <set>
#include <cstdint>
#include <vector>
#include <climits>
#include <iostream>

using namespace std;

#define NUM_VERTICES 4
int edges[NUM_VERTICES][NUM_VERTICES] = 
        {
            { 0, 4, 8, 3 },
            { 4, 0, 4, 13 },
            { 8, 4, 0, 1 },
            { 3, 13, 1, 0 },
        };

    /**
        min = INT_MAX
        for all unvisited v
           min =  min(dist(v), min)
           min_ver = v
        return min_ver
          
    */
int findNearestFromVisited(const std::vector<int32_t>& dist, const std::set<int32_t>& visited)
{
    int32_t min = INT_MAX;
    int32_t ret_v = -1;
    for (int32_t i = 0; i < NUM_VERTICES; i ++) {
        if (not visited.count(i)) {
            if (min >= dist[i]) {
                min = dist[i];
                ret_v = i;
            }
        }
    }
    cout << "ret " << ret_v << endl;
    return ret_v;
}

/**
    dist[u] = 0 ; all else is INT_MAX

    while visited.size != all
       x = findNearest
       add x to visited
       for all adj of x
          if not visited(adj) and edges exists(x, adj) and dist[x] != INT_MAX
            dist[adj] = min(dist[adj], edge[x, adj] + dist[x])

    return dist

 */
void shortestFrom(int32_t u)
{
    std::vector<int32_t> dist(NUM_VERTICES, INT_MAX);
    std::set<int32_t> visited;
    dist[u] = 0;

    while (visited.size() != NUM_VERTICES)
    {
        auto x = findNearestFromVisited(dist, visited);
        visited.insert(x);
        for (int i = 0; i < NUM_VERTICES; i++)
        {
            if (i != x) {
                if (not visited.count(i) && edges[x][i] != INT_MAX && dist[x] != INT_MAX) {
                    dist[i] = std::min(dist[i], edges[x][i] + dist[x]);
                }
            }
        }
    }
    for (auto iter : dist) {
        cout << iter << " ";
    }
    cout << endl;
}

int main()
{
    shortestFrom(2);
}
