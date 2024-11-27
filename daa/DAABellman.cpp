#include <iostream>
#include <vector>
#include <limits.h>
#include <chrono>

using namespace std;
using namespace chrono;

struct Edge {
    int src, dest, weight;
};

class BellmanFord {
    int vertices;
    vector<Edge> edges;

public:
    BellmanFord(int vertices) {
        this->vertices = vertices;
    }

    void addEdge(int src, int dest, int weight) {
        edges.push_back({src, dest, weight});
    }

    void bellmanFord(int source) {
        vector<int> distance(vertices, INT_MAX);
        distance[source] = 0;

        // Step 1: Relax all edges V-1 times
        for (int i = 1; i < vertices; ++i) {
            for (const auto& edge : edges) {
                int u = edge.src;
                int v = edge.dest;
                int weight = edge.weight;
                if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
                    distance[v] = distance[u] + weight;
                }
            }
        }

        // Step 2: Check for negative-weight cycles
        for (const auto& edge : edges) {
            int u = edge.src;
            int v = edge.dest;
            int weight = edge.weight;
            if (distance[u] != INT_MAX && distance[u] + weight < distance[v]) {
                cout << "Graph contains a negative-weight cycle" << endl;
                return;
            }
        }

        // Print the distances from source
        printDistances(distance, source);
    }

private:
    void printDistances(const vector<int>& distance, int source) {
        cout << "Vertex\tDistance from Source " << source << endl;
        for (int i = 0; i < vertices; ++i) {
            if (distance[i] == INT_MAX)
                cout << i << "\t\tInfinity" << endl;
            else
                cout << i << "\t\t" << distance[i] << endl;
        }
    }
};

int main() {
    int vertices, edges;
    cout << "Enter the number of vertices: ";
    cin >> vertices;

    BellmanFord graph(vertices);

    cout << "Enter the number of edges: ";
    cin >> edges;

    cout << "Enter the edges in the format (source destination weight):" << endl;
    for (int i = 0; i < edges; ++i) {
        int src, dest, weight;
        cin >> src >> dest >> weight;
        graph.addEdge(src, dest, weight);
    }

    int source;
    cout << "Enter the source vertex: ";
    cin >> source;

    // Start measuring time
    auto start = high_resolution_clock::now();
    graph.bellmanFord(source);
    auto end = high_resolution_clock::now();

    // Calculate and print elapsed time
    auto duration = duration_cast<microseconds>(end - start).count();
    cout << "Time taken to execute Bellman-Ford algorithm: " << duration << " microseconds" << endl;

    return 0;
}
