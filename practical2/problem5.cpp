#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    
    vector<vector<pair<int, long long>>> graph(N + 1);
    
    for (int i = 0; i < M; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
        graph[v].push_back({u, w});
    }
    
    // Dijkstra's algorithm
    vector<long long> dist(N + 1, LLONG_MAX);
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;
    
    dist[1] = 0;
    pq.push({0, 1});
    
    while (!pq.empty()) {
        long long d = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        
        if (d > dist[u]) continue;
        
        for (int i = 0; i < graph[u].size(); i++) {
            int v = graph[u][i].first;
            long long w = graph[u][i].second;
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                pq.push({dist[v], v});
            }
        }
    }
    
    if (dist[N] == LLONG_MAX) {
        cout << -1 << "\n";
    } else {
        cout << dist[N] << "\n";
    }
    
    return 0;
}
