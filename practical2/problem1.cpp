#include <iostream>
#include <vector>
#include <functional>
using namespace std;

int main() {
    int T;
    cin >> T;
    
    while (T--) {
        int N;
        cin >> N;
        
        vector<int> allergies(N, 0);
        
        // Read allergies as bitmasks
        for (int i = 0; i < N; i++) {
            int M;
            cin >> M;
            for (int j = 0; j < M; j++) {
                int allergy;
                cin >> allergy;
                allergies[i] |= (1 << (allergy - 1));
            }
        }
        
        // Try to find a valid arrangement using backtracking
        vector<int> arrangement;
        vector<bool> used(N, false);
        bool found = false;
        
        function<void(int)> backtrack = [&](int pos) {
            if (found) return;
            
            if (pos == N) {
                found = true;
                return;
            }
            
            for (int i = 0; i < N; i++) {
                if (used[i]) continue;
                
                // Check if this person can be placed
                bool canPlace = true;
                
                // Check with previous person in circular arrangement
                if (pos > 0) {
                    int prev = arrangement[pos - 1];
                    if ((allergies[i] & allergies[prev]) != 0) {
                        canPlace = false;
                    }
                }
                
                // Check with first person (circular table)
                if (canPlace && pos == N - 1 && N > 1) {
                    int first = arrangement[0];
                    if ((allergies[i] & allergies[first]) != 0) {
                        canPlace = false;
                    }
                }
                
                if (canPlace) {
                    used[i] = true;
                    arrangement.push_back(i);
                    backtrack(pos + 1);
                    if (found) return;
                    arrangement.pop_back();
                    used[i] = false;
                }
            }
        };
        
        backtrack(0);
        
        cout << (found ? "YES" : "NO") << "\n";
    }
    
    return 0;
}
