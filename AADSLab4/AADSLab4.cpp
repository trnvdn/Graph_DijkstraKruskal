#include <iostream>
#include <vector>
#include <algorithm> // for std::sort
#include <queue>
using namespace std;

struct Edge {
    int from;
    int to;
    int weight;
};

class GraphWeighted {
private:
    int numVertices;
    vector<Edge> edges;
    vector<vector<int>> adjacencyMatrix;
    vector<vector<Edge>> adjacencyList;

public:
    GraphWeighted() {
        cout << "Enter the number of vertices: ";
        cin >> numVertices;

        int numEdges;
        cout << "Enter the number of edges: ";
        cin >> numEdges;

        edges.resize(numEdges);
        adjacencyList.resize(numVertices);

        
        for (int i = 0; i < numEdges; i++) {
            int from, to, weight;
            cout << "Enter edge " << i + 1 << " (from to weight): ";
            cin >> from >> to >> weight;
            edges[i] = { from, to, weight };

            adjacencyList[from].push_back({ from, to, weight });
            adjacencyList[to].push_back({ to, from, weight });
        }
        for (int i = 1; i < numEdges; i++) {
            Edge temp = edges[i];
            int j = i - 1;
            while (j >= 0 && edges[j].weight > temp.weight) {
                edges[j + 1] = edges[j];
                j--;
            }
            edges[j + 1] = temp;
        }

        adjacencyMatrix.resize(numVertices);
        for (int i = 0; i < numVertices; i++) {
            adjacencyMatrix[i].resize(numVertices);
            for (int j = 0; j < numVertices; j++) {
                adjacencyMatrix[i][j] = 0;
            }
        }
    }

    void printGraph() {
        cout << "Adjacency Matrix:" << endl;
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                cout << adjacencyMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    void kruskal() {
        vector<int> parent(numVertices);
        for (int i = 0; i < numVertices; i++) {
            parent[i] = i;
        }

        int edgeCount = 0;
        int index = 0;
        while (edgeCount < numVertices - 1 && index < edges.size()) {
            Edge nextEdge = edges[index];
            index++;

            int parent1 = parent[nextEdge.from];
            int parent2 = parent[nextEdge.to];

            if (parent1 != parent2) {
                adjacencyMatrix[nextEdge.from][nextEdge.to] = nextEdge.weight;
                adjacencyMatrix[nextEdge.to][nextEdge.from] = nextEdge.weight;

                edgeCount++;

                for (int i = 0; i < numVertices; i++) {
                    if (parent[i] == parent2) {
                        parent[i] = parent1;
                    }
                }
            }
        }
    }
    void dijkstra(int source) {
        vector<int> distances(numVertices, numeric_limits<int>::max());
        distances[source] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({ 0, source });

        while (!pq.empty()) {
            int current = pq.top().second;
            pq.pop();

            for (int i = 0; i < adjacencyList[current].size(); i++) {
                int next = adjacencyList[current][i].to;
                int weight = adjacencyList[current][i].weight;

                if (distances[current] + weight < distances[next]) {
                    distances[next] = distances[current] + weight;
                    pq.push({ distances[next], next });
                }
            }
        }

        // Print the shortest distances to all nodes
        cout << "Shortest distances from source node " << source << ":" << endl;
        for (int i = 0; i < numVertices; i++) {
            cout << "Node " << i << ": " << distances[i] << endl;
        }
    }
};

int main() {
    GraphWeighted g;
    g.kruskal();
    g.printGraph();
    g.dijkstra(0);
    return 0;
}
