#include <iostream>
#include <queue>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
    int n;
    cin >> n;

    priority_queue<int> lowerHalf;
    priority_queue<int, vector<int>, greater<int>> upperHalf;

    cout << fixed << setprecision(1);

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;

        if (lowerHalf.empty() || x <= lowerHalf.top()) {
            lowerHalf.push(x);
        } else {
            upperHalf.push(x);
        }

        if (lowerHalf.size() > upperHalf.size() + 1) {
            upperHalf.push(lowerHalf.top());
            lowerHalf.pop();
        } else if (upperHalf.size() > lowerHalf.size()) {
            lowerHalf.push(upperHalf.top());
            upperHalf.pop();
        }

        if (lowerHalf.size() == upperHalf.size()) {
            double median = (lowerHalf.top() + upperHalf.top()) / 2.0;
            cout << median << "\n";
        } else {
            cout << static_cast<double>(lowerHalf.top()) << "\n";
        }
    }

    return 0;
}
