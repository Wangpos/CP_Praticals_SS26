#include <iostream>
#include <vector>
#include <climits>
#include <iomanip>

using namespace std;

const int INF = INT_MAX;

// Floyd Warshall Algorithm - Finds shortest paths between all pairs of vertices
// Time Complexity: O(V^3)
// Space Complexity: O(V^2)

class FloydWarshall {
private:
    int V;  // Number of vertices
    vector<vector<int>> dist;  // Distance matrix
    vector<vector<int>> next;  // Path reconstruction matrix

public:
    FloydWarshall(int vertices) : V(vertices) {
        dist.assign(V, vector<int>(V, INF));
        next.assign(V, vector<int>(V, -1));
        
        // Distance from a vertex to itself is 0
        for (int i = 0; i < V; i++) {
            dist[i][i] = 0;
            next[i][i] = i;
        }
    }

    // Add an edge to the graph
    void addEdge(int u, int v, int weight) {
        dist[u][v] = min(dist[u][v], weight);
        next[u][v] = v;
    }

    // Floyd Warshall Algorithm
    void floydWarshall() {
        // k is the intermediate vertex
        for (int k = 0; k < V; k++) {
            for (int i = 0; i < V; i++) {
                for (int j = 0; j < V; j++) {
                    if (dist[i][k] != INF && dist[k][j] != INF) {
                        if (dist[i][k] + dist[k][j] < dist[i][j]) {
                            dist[i][j] = dist[i][k] + dist[k][j];
                            next[i][j] = next[i][k];
                        }
                    }
                }
            }
        }
    }

    // Print the distance matrix
    void printDistances() {
        cout << "\nShortest Distance Matrix:\n";
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

    // Print the shortest path from u to v
    void printPath(int u, int v) {
        if (dist[u][v] == INF) {
            cout << "No path exists from " << u << " to " << v << "\n";
            return;
        }

        cout << "Path from " << u << " to " << v << ": ";
        int current = u;
        while (current != v) {
            cout << current << " -> ";
            current = next[current][v];
        }
        cout << v << "\n";
        cout << "Distance: " << dist[u][v] << "\n";
    }

    // Check for negative cycles
    bool hasNegativeCycle() {
        for (int i = 0; i < V; i++) {
            if (dist[i][i] < 0) {
                return true;
            }
        }
        return false;
    }
};

int main() {
    cout << "===== Floyd Warshall Algorithm =====\n";
    
    // Test Case 1: Simple graph
    cout << "\nTest Case 1: Simple Graph\n";
    FloydWarshall fw1(4);
    
    // Add edges: (u, v, weight)
    fw1.addEdge(0, 1, 5);
    fw1.addEdge(0, 3, 10);
    fw1.addEdge(1, 2, 3);
    fw1.addEdge(2, 3, 1);
    
    fw1.floydWarshall();
    fw1.printDistances();
    fw1.printPath(0, 3);
    fw1.printPath(0, 2);
    
    // Test Case 2: Complete graph
    cout << "\n\nTest Case 2: Complete Graph\n";
    FloydWarshall fw2(3);
    
    fw2.addEdge(0, 1, 2);
    fw2.addEdge(1, 0, 4);
    fw2.addEdge(1, 2, 1);
    fw2.addEdge(2, 0, 8);
    fw2.addEdge(2, 1, 10);
    fw2.addEdge(0, 2, 7);
    
    fw2.floydWarshall();
    fw2.printDistances();
    
    cout << "\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i != j) {
                fw2.printPath(i, j);
            }
        }
    }
    
    // Test Case 3: Disconnected graph
    cout << "\n\nTest Case 3: Disconnected Graph\n";
    FloydWarshall fw3(4);
    
    fw3.addEdge(0, 1, 1);
    fw3.addEdge(1, 0, 1);
    fw3.addEdge(2, 3, 2);
    fw3.addEdge(3, 2, 2);
    
    fw3.floydWarshall();
    fw3.printDistances();
    fw3.printPath(0, 2);
    
    return 0;
}
