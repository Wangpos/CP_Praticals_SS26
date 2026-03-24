#include <iostream>
#include <vector>
using namespace std;

int main() {
    int T;
    cin >> T;
    
    while (T--) {
        int N, K;
        cin >> N >> K;
        
        vector<int> arr(N);
        for (int i = 0; i < N; i++) {
            cin >> arr[i];
        }
        
        int maxAnd = 0;
        
        // Try each bit from MSB (bit 29) to LSB (bit 0)
        for (int bit = 29; bit >= 0; bit--) {
            int candidate = maxAnd | (1 << bit);  // Try setting this bit
            
            // Check if any subarray of length K has AND == candidate
            bool found = false;
            for (int i = 0; i <= N - K && !found; i++) {
                int andVal = arr[i];
                for (int j = i + 1; j < i + K; j++) {
                    andVal &= arr[j];
                }
                // Check if this subarray's AND has all bits of candidate set
                if ((andVal & candidate) == candidate) {
                    found = true;
                }
            }
            
            if (found) {
                maxAnd = candidate;  // Keep this bit
            }
        }
        
        cout << maxAnd << "\n";
    }
    
    return 0;
}
