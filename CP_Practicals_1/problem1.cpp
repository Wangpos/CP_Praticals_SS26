#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> arr(n);
    long long sum = 0;

    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
        sum += arr[i];
    }

    cout << *max_element(arr.begin(), arr.end()) << "\n";
    cout << *min_element(arr.begin(), arr.end()) << "\n";
    cout << sum << "\n";

    return 0;
}
