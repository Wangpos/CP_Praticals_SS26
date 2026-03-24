#include <iostream>
#include <vector>
#include <deque>
using namespace std;

int main() {
    int N, K;
    cin >> N >> K;
    
    vector<int> arr(N);
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    
    deque<int> dq; // stores indices
    
    // Process first window
    for (int i = 0; i < K; i++) {
        // Remove elements outside current window
        while (!dq.empty() && dq.front() < 0) {
            dq.pop_front();
        }
        
        // Remove smaller elements from back
        while (!dq.empty() && arr[dq.back()] <= arr[i]) {
            dq.pop_back();
        }
        
        dq.push_back(i);
    }
    
    // Print maximum of first window
    cout << arr[dq.front()];
    
    // Process remaining elements
    for (int i = K; i < N; i++) {
        // Remove elements outside current window
        while (!dq.empty() && dq.front() <= i - K) {
            dq.pop_front();
        }
        
        // Remove smaller elements from back
        while (!dq.empty() && arr[dq.back()] <= arr[i]) {
            dq.pop_back();
        }
        
        dq.push_back(i);
        
        cout << " " << arr[dq.front()];
    }
    
    cout << "\n";
    
    return 0;
}
