
using namespace std;
#include <iostream>
#include <strings.h>
#include <queue>

static const int NUM_NODES = 5;

struct Graph {
	
	int **adjmatrix = 0;

	Graph(int num_nodes) {
		// std::cout << sizeof(this->adjmatrix[0][0]) << std::endl;
		// std::cout << this->adjmatrix << "," << &this->adjmatrix << std::endl;
		this->adjmatrix = new int*[num_nodes];
		for (int i = 0; i < num_nodes; i++) {
			adjmatrix[i] = new int[num_nodes];
		}
		//bzero(&this->adjmatrix, sizeof(this->adjmatrix[0]) * NUM_NODES);
	}

	void addEdge(int from, int to) {
		adjmatrix[from][to] = adjmatrix[to][from] = 1;
	}

	bool bfs(int from, int to) {
		int start = from;
		int visited[NUM_NODES];
		bzero(&visited, sizeof(visited));

		std::queue<int> to_visit;
		to_visit.push(from);
		visited[from] = 1;

		bool found = false;
		do {
			int current = to_visit.front();
			to_visit.pop();
			if (current == to) {
				found = true;
				break;
			}
			for (int i = 0; i < NUM_NODES; i++) {
				if (i != current) {
					int is_exists = this->adjmatrix[current][i];
					if (is_exists) { // node exists
						if (!visited[i]) {
							to_visit.push(i);
							visited[i] = 1;
						}
					}
				}
			}
		} while (to_visit.size());
		return found;
	}

	void print() {
		for (int i = 0; i < NUM_NODES; i++) {
			for (int j = 0; j < NUM_NODES; j++)
				std::cout << this->adjmatrix[i][j] << ",";
			std::cout << std::endl;
		}
	}
};


int main() {

	auto a = new Graph(5);
	a->addEdge(1, 3);
	a->addEdge(2, 4);
	a->addEdge(0, 1);
	a->print();
	for (int i = 0; i < NUM_NODES; i++) {
		for (int j = i+1; j < NUM_NODES; j++)
			if (i != j)
				std::cout << "path from " << i << "->" << j << " is " <<  a->bfs(i, j) << std::endl;
	}
}

