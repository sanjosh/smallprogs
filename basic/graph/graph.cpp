#include <vector>
#include <set>
#include <queue>
#include <iostream>

using namespace std;

class Graph
{
    int32_t maxV_ = 0;
    std::vector<std::set<int32_t>> adj_list_;

    public:

    explicit Graph(int32_t maxV) : maxV_(maxV)
    {
        adj_list_.resize(maxV);
    }

    void AddEdge(int32_t v, int32_t w)
    {
        adj_list_[v].insert(w);
        adj_list_[w].insert(v);
    }

    bool IsAdjacent(int32_t v, int32_t w) const
    {
        return (adj_list_[v].count(w) > 0);
    }

    const std::set<int32_t> GetAdjacent(int32_t v) const 
    {
        return adj_list_[v];
    }

    void BFS() const {

        std::queue<int32_t> q;
        std::set<int32_t> visited;

        q.push(0);
        visited.insert(0);

        while (q.size()) {
            auto cur = q.front();
            q.pop();
            visited.insert(cur);
            cout << "bfs visiting " << cur << endl;

            auto v_list = GetAdjacent(cur);
            for (auto v : v_list) {
                if (visited.find(v) == visited.end()) {
                    q.push(v);
                }
            }
        }
    }

    std::set<int32_t> visited_;

    void InitDFS() {
        visited_.clear();
    }

    bool DFS(int32_t cur) {

        visited_.insert(cur);
        cout << "dfs visiting " << cur << endl;
        auto adj_list = GetAdjacent(cur);
        for (auto v : adj_list) {
            if (visited_.count(v) == 0) {
                if (DFS(v) == true) {
                    return true;
                }
            }
        }
        return false;
    }
};

int main()
{
    auto g = Graph(20);

    g.AddEdge(0, 3);
    g.AddEdge(0, 9);
    g.AddEdge(0, 7);
    g.AddEdge(0, 19);
    g.AddEdge(3, 8);
    g.AddEdge(3, 12);
    g.AddEdge(3, 16);

    cout << g.IsAdjacent(8, 3) << endl;

    g.BFS();

    g.InitDFS();
    cout << g.DFS(0) << endl;
}
