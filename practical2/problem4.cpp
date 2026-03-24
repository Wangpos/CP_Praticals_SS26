#include <iostream>
#include <vector>
#include <map>
#include <climits>
using namespace std;

int main() {
    int N, K, Q;
    cin >> N >> K >> Q;
    
    vector<int> arr(N);
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    
    auto getMaxInWindow = [&](int endIdx) {
        int maxVal = INT_MIN;
        int startIdx = max(0, endIdx - K + 1);
        for (int i = startIdx; i <= endIdx; i++) {
            maxVal = max(maxVal, arr[i]);
        }
        return maxVal;
    };
    
    for (int q = 0; q < Q; q++) {
        int type;
        cin >> type;
        
        if (type == 1) {
            // Update query
            int pos, val;
            cin >> pos >> val;
            arr[pos] = val; // pos is already 0-indexed
        } else {
            // Query for maximum
            int idx;
            cin >> idx;
            int maxVal = getMaxInWindow(idx - 1); // Convert to 0-based indexing
            cout << maxVal << "\n";
        }
    }
    
    return 0;
}
