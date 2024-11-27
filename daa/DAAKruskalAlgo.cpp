#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct Edge {
    char u, v;
    int weight;
};

bool compare(Edge a, Edge b) {
    return a.weight < b.weight;
}

char findParent(char u, unordered_map<char, char>& parent) {
    if (parent[u] == u) return u;
    return parent[u] = findParent(parent[u], parent);
}

void unionSets(char u, char v, unordered_map<char, char>& parent, unordered_map<char, int>& rank) {
    u = findParent(u, parent);
    v = findParent(v, parent);
    
    if (rank[u] < rank[v]) {
        parent[u] = v;
    } else if (rank[u] > rank[v]) {
        parent[v] = u;
    } else {
        parent[v] = u;
        rank[u]++;
    }
}

void kruskal(vector<Edge>& edges) {

    sort(edges.begin(), edges.end(), compare);

    unordered_map<char, char> parent;
    unordered_map<char, int> rank;

    for (char c = 'A'; c < 'A' + edges.size(); c++) {
        parent[c] = c;
        rank[c] = 0;
    }

    vector<Edge> mst; 
    int mstWeight = 0;

    for (Edge edge : edges) {
       
        char rootU = findParent(edge.u, parent);
        char rootV = findParent(edge.v, parent);

        if (rootU != rootV) {
            mst.push_back(edge);      
            mstWeight += edge.weight; 
            unionSets(rootU, rootV, parent, rank); 
        }
    }

    cout << "Minimum Spanning Tree (MST) contains the following edges:\n";
    for (Edge edge : mst) {
        cout << edge.u << " -- " << edge.v << " == " << edge.weight << "\n";
    }
    cout << "Total weight of MST: " << mstWeight << "\n";
}

int main() {
    int E;
    cout << "Enter the number of edges: ";
    cin >> E;

    vector<Edge> edges(E);

    cout << "Enter the edges in the format (u v weight):\n";
    for (int i = 0; i < E; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    auto start = high_resolution_clock::now();
    kruskal(edges);
    auto end = high_resolution_clock::now();

    auto time_spent = duration_cast<nanoseconds>(end - start).count();
    cout << "\nThe elapsed time for " << E << " edges is " << time_spent << " nanoseconds" << endl;

    cout<<endl;
    return 0;
}
