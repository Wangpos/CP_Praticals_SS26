#include <iostream>
#include <vector>

using namespace std;

int main() {
    int N;
    cin >> N;

    vector<int> numbers(N);
    for (int i = 0; i < N; i++) {
        cin >> numbers[i];
    }

    int totalSubsets = 1 << N;
    int evenSumCount = 0;

    for (int mask = 0; mask < totalSubsets; mask++) {
        int subsetSum = 0;

        for (int i = 0; i < N; i++) {
            if (mask & (1 << i)) {
                subsetSum += numbers[i];
            }
        }

        if (subsetSum % 2 == 0) {
            evenSumCount++;
        }
    }

    cout << evenSumCount << '\n';

    return 0;
}