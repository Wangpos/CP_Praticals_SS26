#include <iostream>
#include <map>
#include <queue>
#include <tuple>
#include <climits>
using namespace std;

int main() {
    int N, M, K;
    cin >> N >> M >> K;
    
    vector<int> toll(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> toll[i];
    }
    
    // dp[i][j][s] = minimum time to reach booth i with j coins and s skips used
    // But this might be too memory intensive, so let's use a BFS approach
    
    map<tuple<int, int, int>, int> visited; // (booth, coins, skips_used) -> min_time
    priority_queue<tuple<int, int, int, int>, vector<tuple<int, int, int, int>>, greater<tuple<int, int, int, int>>> pq;
    
    // (time, booth, coins, skips_used)
    // Start at booth 1 (1-indexed), destination is booth N
    pq.push({0, 1, M, 0});
    
    int minTime = INT_MAX;
    
    while (!pq.empty()) {
        int time = get<0>(pq.top());
        int booth = get<1>(pq.top());
        int coins = get<2>(pq.top());
        int skips = get<3>(pq.top());
        pq.pop();
        
        // Reached the destination booth N
        if (booth == N) {
            minTime = min(minTime, time);
            continue;
        }
        
        auto state = make_tuple(booth, coins, skips);
        if (visited.count(state) && visited[state] <= time) {
            continue;
        }
        visited[state] = time;
        
        // Option 1: Pay toll and move to next booth
        if (coins >= toll[booth]) {
            pq.push({time + 1, booth + 1, coins - toll[booth], skips});
        }
        
        // Option 2: Skip this booth (if we haven't skipped K times)
        if (skips < K) {
            pq.push({time + 2, booth + 1, coins, skips + 1});
        }
    }
    
    if (minTime == INT_MAX) {
        cout << -1 << "\n";
    } else {
        cout << minTime << "\n";
    }
    
    return 0;
}
