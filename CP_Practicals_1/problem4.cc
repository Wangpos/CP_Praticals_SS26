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

	deque<int> dq; // stores indices of useful elements in decreasing value order
	for (int i = 0; i < N; i++) {
		while (!dq.empty() && dq.front() <= i - K) {
			dq.pop_front();
		}

		while (!dq.empty() && arr[dq.back()] <= arr[i]) {
			dq.pop_back();
		}

		dq.push_back(i);

		if (i >= K - 1) {
			cout << arr[dq.front()];
			if (i < N - 1) {
				cout << " ";
			}
		}
	}

	return 0;
}
