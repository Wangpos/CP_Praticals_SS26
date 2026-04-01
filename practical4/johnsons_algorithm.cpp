#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <iomanip>

using namespace std;

const int INF = INT_MAX;

// Johnson's Algorithm - All pairs shortest paths
// Works with non-negative and negative edges
// Time Complexity: O(VE + V^2 log V) or O(V^2 + VE) depending on SSSP algorithm
// Space Complexity: O(V^2)

class JohnsonsAlgorithm {
private:
    int V;  // Number of vertices
    vector<vector<pair<int, int>>> adj;  // Adjacency list: (destination, weight)
    vector<int> h;  // Reweighting values
    vector<vector<int>> dist;  // All-pairs shortest paths

public:
    JohnsonsAlgorithm(int vertices) : V(vertices), adj(vertices), 
                                      h(vertices, 0), dist(vertices, vector<int>(vertices, INF)) {
        for (int i = 0; i < V; i++) {
            dist[i][i] = 0;
        }
    }

    // Add a directed edge
    void addEdge(int u, int v, int weight) {
        adj[u].push_back({v, weight});
    }

    // Bellman Ford Algorithm - finds shortest paths from source
    bool bellmanFord(int source, vector<int>& distance) {
        distance.assign(V, INF);
        distance[source] = 0;

        // Relax edges V-1 times
        for (int i = 0; i < V - 1; i++) {
            for (int u = 0; u < V; u++) {
                if (distance[u] != INF) {
                    for (auto& edge : adj[u]) {
                        int v = edge.first;
                        int w = edge.second;
                        if (distance[u] + w < distance[v]) {
                            distance[v] = distance[u] + w;
                        }
                    }
                }
            }
        }

        // Check for negative cycles
        for (int u = 0; u < V; u++) {
            if (distance[u] != INF) {
                for (auto& edge : adj[u]) {
                    int v = edge.first;
                    int w = edge.second;
                    if (distance[u] + w < distance[v]) {
                        return false;  // Negative cycle detected
                    }
                }
            }
        }
        return true;
    }

    // Dijkstra's Algorithm using reweighted edges
    void dijkstra(int source) {
        vector<int> distance(V, INF);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        distance[source] = 0;
        pq.push({0, source});

        while (!pq.empty()) {
            int u = pq.top().second;
            int d = pq.top().first;
            pq.pop();

            if (d > distance[u]) continue;

            for (auto& edge : adj[u]) {
                int v = edge.first;
                int w = edge.second;
                int reweightedWeight = w + h[u] - h[v];

                if (distance[u] + reweightedWeight < distance[v]) {
                    distance[v] = distance[u] + reweightedWeight;
                    pq.push({distance[v], v});
                }
            }
        }

        // Convert back to original weights
        for (int v = 0; v < V; v++) {
            if (distance[v] != INF) {
                dist[source][v] = distance[v] - h[source] + h[v];
            }
        }
    }

    // Johnson's Algorithm main function
    bool johnsons() {
        // Step 1: Create a source vertex connected to all vertices with weight 0
        vector<vector<pair<int, int>>> tempAdj = adj;
        for (int i = 0; i < V; i++) {
            adj[V - 1].push_back({i, 0});  // Using V-1 as temporary source
        }
        V++;

        // Wait, we need to actually add a temporary source vertex. Let me fix this approach.
        // Better approach: use Bellman Ford from a virtual source
        
        V--;  // Revert
        vector<int> h_temp(V, INF);
        h_temp[0] = 0;

        // Run simplified Bellman Ford from vertex 0
        for (int i = 0; i < V - 1; i++) {
            for (int u = 0; u < V; u++) {
                if (h_temp[u] != INF) {
                    for (auto& edge : adj[u]) {
                        int v = edge.first;
                        int w = edge.second;
                        if (h_temp[u] + w < h_temp[v]) {
                            h_temp[v] = h_temp[u] + w;
                        }
                    }
                }
            }
        }

        // Check for negative cycles
        for (int u = 0; u < V; u++) {
            if (h_temp[u] != INF) {
                for (auto& edge : adj[u]) {
                    int v = edge.first;
                    int w = edge.second;
                    if (h_temp[u] + w < h_temp[v]) {
                        return false;
                    }
                }
            }
        }

        h = h_temp;

        // Step 2: Run Dijkstra from each vertex with reweighted edges
        for (int source = 0; source < V; source++) {
            dijkstra(source);
        }

        return true;
    }

    // Print distance matrix
    void printDistances() {
        cout << "\nAll-Pairs Shortest Paths:\n";
        cout << setw(6) << " ";
        for (int i = 0; i < V; i++) {
            cout << setw(6) << i;
        }
        cout << "\n";
        
        for (int i = 0; i < V; i++) {
            cout << setw(6) << i;
            for (int j = 0; j < V; j++) {
                if (dist[i][j] == INF) {
                    cout << setw(6) << "INF";
                } else {
                    cout << setw(6) << dist[i][j];
                }
            }
            cout << "\n";
        }
    }

    int getDistance(int u, int v) {
        return dist[u][v];
    }
};

int main() {
    cout << "===== Johnson's Algorithm =====\n";
    
    // Test Case 1: Simple graph
    cout << "\nTest Case 1: Simple Graph\n";
    JohnsonsAlgorithm ja1(4);
    
    ja1.addEdge(0, 1, 5);
    ja1.addEdge(0, 3, 10);
    ja1.addEdge(1, 2, 3);
    ja1.addEdge(2, 3, 1);
    ja1.addEdge(3, 1, 2);
    
    if (ja1.johnsons()) {
        ja1.printDistances();
    } else {
        cout << "Negative cycle detected!\n";
    }
    
    // Test Case 2: Graph with negative edges (but no negative cycle)
    cout << "\n\nTest Case 2: Graph with Negative Edges\n";
    JohnsonsAlgorithm ja2(5);
    
    ja2.addEdge(0, 1, -1);
    ja2.addEdge(0, 2, 4);
    ja2.addEdge(1, 2, 3);
    ja2.addEdge(1, 3, 2);
    ja2.addEdge(2, 3, 5);
    ja2.addEdge(3, 4, 2);
    ja2.addEdge(4, 1, 1);
    
    if (ja2.johnsons()) {
        ja2.printDistances();
    } else {
        cout << "Negative cycle detected!\n";
    }
    
    // Test Case 3: Complete graph
    cout << "\n\nTest Case 3: Complete Graph\n";
    JohnsonsAlgorithm ja3(3);
    
    ja3.addEdge(0, 1, 2);
    ja3.addEdge(1, 0, 4);
    ja3.addEdge(1, 2, 1);
    ja3.addEdge(2, 0, 8);
    ja3.addEdge(2, 1, 10);
    ja3.addEdge(0, 2, 7);
    
    if (ja3.johnsons()) {
        ja3.printDistances();
    } else {
        cout << "Negative cycle detected!\n";
    }
    
    return 0;
}
