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

    for (int mask = 0; mask < totalSubsets; mask++) {
        cout << "{";

        bool first = true;
        for (int i = 0; i < N; i++) {
            if (mask & (1 << i)) {
                if (!first) {
                    cout << " ";
                }
                cout << numbers[i];
                first = false;
            }
        }

        cout << "}" << '\n';
    }

    return 0;
}