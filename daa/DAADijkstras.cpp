#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <climits>
#include <chrono>

using namespace std;
using namespace chrono;

typedef pair<int, int> pii;

void addEdge(vector<vector<pii>>& graph, int u, int v, int weight) {
    graph[u].push_back({weight, v});
    graph[v].push_back({weight, u});
}

vector<int> dijkstra(const vector<vector<pii>>& graph, int source) {
    int V = graph.size();
    vector<int> dist(V, INT_MAX);
    priority_queue<pii, vector<pii>, greater<pii>> pq;

    dist[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        int u = pq.top().second;
        int uDist = pq.top().first;
        pq.pop();

        if (uDist > dist[u]) continue;

        for (const auto& edge : graph[u]) {
            int weight = edge.first;
            int v = edge.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

int main() {
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;

    vector<vector<pii>> graph(V);

    cout << "Enter the edges in the format (u v weight):" << endl;
    for (int i = 0; i < E; ++i) {
        int u, v, weight;
        cin >> u >> v >> weight;
        addEdge(graph, u, v, weight);
    }

    int source;
    cout << "Enter the source vertex: ";
    cin >> source;

    auto start = high_resolution_clock::now();
    vector<int> distances = dijkstra(graph, source);
    auto end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start).count();
    cout << "Time taken to execute Dijkstra's algorithm: " << duration << " microseconds" << endl;

    cout << "Vertex\tDistance from Source " << source << endl;
    for (int i = 0; i < V; ++i) {
        cout << i << "\t\t" << distances[i] << endl;
    }

    return 0;
}
