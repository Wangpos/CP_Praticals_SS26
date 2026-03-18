#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N, target;
    cin >> N >> target;

    vector<int> arr(N);
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }

    vector<vector<long long>> dp(N + 1, vector<long long>(target + 1, 0));

    for (int i = 0; i <= N; i++) {
        dp[i][0] = 1;
    }

    for (int i = 1; i <= N; i++) {
        for (int j = 0; j <= target; j++) {
            dp[i][j] = dp[i - 1][j];

            if (j >= arr[i - 1]) {
                dp[i][j] += dp[i - 1][j - arr[i - 1]];
            }
        }
    }

    cout << dp[N][target] << "\n";

    return 0;
}
