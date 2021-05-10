#include <vector>
#include <set>
#include <queue>
#include <iostream>

using namespace std;

class Graph
{
    static constexpr int32_t kMaxV = 20;
    std::vector<int32_t> adj_list_[kMaxV];

    public:

    explicit Graph() 
    {
        for (int32_t i = 0; i < kMaxV; i++)
        {
            this->adj_list_[i].resize(kMaxV);
        }
    }

    void AddEdge(int32_t v, int32_t w)
    {
        this->adj_list_[v][w] = 1;
        this->adj_list_[w][v] = 1;
    }

    bool IsAdjacent(int32_t v, int32_t w) const
    {
        return (this->adj_list_[v][w] == 1);
    }

    std::vector<int32_t> GetAdjacent(int32_t v) const 
    {
        std::vector<int32_t> adj;

        for (int32_t i = 0; i < kMaxV; i++)
        {
            if (this->adj_list_[v][i]) {
                adj.push_back(i);
            }
        }
        return adj;
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
            cout << "visiting " << cur << endl;

            auto v_list = this->GetAdjacent(cur);
            for (auto v : v_list) {
                if (visited.find(v) == visited.end()) {
                    q.push(v);
                }
            }
        }
    }
};

int main()
{
    auto g = Graph();

    g.AddEdge(0, 3);
    g.AddEdge(0, 9);
    g.AddEdge(0, 7);
    g.AddEdge(0, 19);
    g.AddEdge(3, 8);
    g.AddEdge(3, 12);
    g.AddEdge(3, 16);

    cout << g.IsAdjacent(2, 3) << endl;

    g.BFS();
}
