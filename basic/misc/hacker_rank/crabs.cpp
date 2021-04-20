#include <assert.h>
#include <stdio.h>

/*from hackerrank*/

#define MAXV 100

int graph[MAXV][MAXV];
int degree[MAXV];

int vertices;
int crab_degree;
int edges;

class Node
{
    list<int> edges;

        
};

vector<Node*> nodeVec;



int main()
{
    bzero(degree, sizeof(degree));
    bzero(graph, sizeof(graph));

    scanf("%d %d %d\n", &vertices, &crab_degree, &edges);

    assert(crab_degree >=2 && crab_degree <= 100);
    assert(vertices >=2 && vertices <= 100);
    assert(edges >= 0 && edges <= ((vertices * (vertices-1)/2)));
    
    for (int i = 0; i < edges; i++)
    {
        int v1, v2;
        scanf("%d %d\n", &v1, v2);
        assert(v1 < vertices);
        assert(v2 < vertices);
        graph[v1] = v2;
        graph[v2] = v1;
        degree[v1] ++;
        degree[v2] ++;
    }

    struct Candidate
    {
        int head;
        int *feet;

        Candidate(int head)
        {
            feet = new int [crab_degree];
        }
        virtual ~Candidate()
        {
            delete [] feet;
        }
    };

    list 

    for (int i = 0; i < vertices; i++)
    {
        if (degree[i] >= crab_degree)
        {   
        }
    }
}


