#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

// Boruvka's Algorithm - Minimum Spanning Tree (MST)
// Time Complexity: O(E log V)
// Space Complexity: O(V + E)

struct Edge {
    int u, v, weight;
    
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

class UnionFind {
private:
    vector<int> parent, rank;

public:
    UnionFind(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    // Find set of an element with path compression
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    // Union two sets with union by rank
    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX == rootY) return false;

        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
        return true;
    }
};

class BoruvkaAlgorithm {
private:
    int V, E;
    vector<Edge> edges;
    vector<pair<pair<int, int>, int>> mst;  // MST edges
    int totalWeight;

public:
    BoruvkaAlgorithm(int vertices, int edgesCount) : V(vertices), E(edgesCount), totalWeight(0) {}

    // Add an undirected edge
    void addEdge(int u, int v, int weight) {
        edges.push_back({u, v, weight});
    }

    // Boruvka's Algorithm
    void boruvka() {
        if (V == 1) {
            cout << "Single vertex - no edges needed\n";
            return;
        }

        // Sort edges by weight for easier processing
        sort(edges.begin(), edges.end());

        UnionFind uf(V);
        vector<int> mstEdges;
        mst.clear();
        totalWeight = 0;

        // Continue until we have V-1 edges in MST
        while (mstEdges.size() < V - 1 && !edges.empty()) {
            // For each component, find minimum weight outgoing edge
            vector<int> minEdge(V, -1);

            for (int i = 0; i < edges.size(); i++) {
                int u = edges[i].u;
                int v = edges[i].v;
                int componentU = uf.find(u);
                int componentV = uf.find(v);

                // Edge connects two different components
                if (componentU != componentV) {
                    if (minEdge[componentU] == -1 ||
                        edges[i].weight < edges[minEdge[componentU]].weight) {
                        minEdge[componentU] = i;
                    }
                    if (minEdge[componentV] == -1 ||
                        edges[i].weight < edges[minEdge[componentV]].weight) {
                        minEdge[componentV] = i;
                    }
                }
            }

            // Add all minimum edges that don't create cycles
            for (int i = 0; i < V; i++) {
                if (minEdge[i] != -1) {
                    int u = edges[minEdge[i]].u;
                    int v = edges[minEdge[i]].v;
                    int w = edges[minEdge[i]].weight;

                    if (uf.unite(u, v)) {
                        mstEdges.push_back(minEdge[i]);
                        mst.push_back({{u, v}, w});
                        totalWeight += w;
                    }
                }
            }
        }

        if (mstEdges.size() != V - 1) {
            cout << "Graph is not connected!\n";
        }
    }

    // Print MST
    void printMST() {
        cout << "\nMinimum Spanning Tree (Boruvka's Algorithm):\n";
        cout << "Edges in MST:\n";
        
        int edgeNumber = 1;
        for (auto& edge : mst) {
            cout << "Edge " << edgeNumber++ << ": (" << edge.first.first << ", " 
                 << edge.first.second << ") - Weight: " << edge.second << "\n";
        }

        cout << "\nTotal Weight of MST: " << totalWeight << "\n";
        cout << "Number of Edges: " << mst.size() << "\n";
    }

    // Alternative simpler implementation using Kruskal's approach
    void boruvkaKruskal() {
        mst.clear();
        totalWeight = 0;

        sort(edges.begin(), edges.end());
        UnionFind uf(V);

        cout << "\nUsing Kruskal-style approach (for comparison):\n";
        
        for (auto& edge : edges) {
            if (uf.unite(edge.u, edge.v)) {
                mst.push_back({{edge.u, edge.v}, edge.weight});
                totalWeight += edge.weight;
                
                if (mst.size() == V - 1) break;
            }
        }
    }

    int getTotalWeight() const {
        return totalWeight;
    }

    int getMSTSize() const {
        return mst.size();
    }
};

int main() {
    cout << "===== Boruvka's Algorithm (MST) =====\n";
    
    // Test Case 1: Simple graph
    cout << "\nTest Case 1: Simple Graph (6 vertices, 9 edges)\n";
    BoruvkaAlgorithm ba1(6, 9);
    
    ba1.addEdge(0, 1, 4);
    ba1.addEdge(0, 2, 2);
    ba1.addEdge(1, 2, 1);
    ba1.addEdge(1, 3, 5);
    ba1.addEdge(2, 3, 8);
    ba1.addEdge(2, 4, 10);
    ba1.addEdge(3, 4, 2);
    ba1.addEdge(3, 5, 6);
    ba1.addEdge(4, 5, 3);
    
    ba1.boruvka();
    ba1.printMST();
    
    // Test Case 2: Complete graph
    cout << "\n\nTest Case 2: Complete Graph (4 vertices)\n";
    BoruvkaAlgorithm ba2(4, 6);
    
    ba2.addEdge(0, 1, 10);
    ba2.addEdge(0, 2, 6);
    ba2.addEdge(0, 3, 5);
    ba2.addEdge(1, 2, 15);
    ba2.addEdge(1, 3, 4);
    ba2.addEdge(2, 3, 12);
    
    ba2.boruvka();
    ba2.printMST();
    
    // Test Case 3: Square graph
    cout << "\n\nTest Case 3: Square Graph (4 vertices)\n";
    BoruvkaAlgorithm ba3(4, 5);
    
    ba3.addEdge(0, 1, 1);
    ba3.addEdge(1, 2, 2);
    ba3.addEdge(2, 3, 1);
    ba3.addEdge(3, 0, 3);
    ba3.addEdge(0, 2, 4);
    
    ba3.boruvka();
    ba3.printMST();
    
    // Test Case 4: Disconnected graph
    cout << "\n\nTest Case 4: Disconnected Graph\n";
    BoruvkaAlgorithm ba4(5, 4);
    
    ba4.addEdge(0, 1, 1);
    ba4.addEdge(1, 2, 2);
    ba4.addEdge(3, 4, 5);
    
    ba4.boruvka();
    ba4.printMST();
    
    return 0;
}
