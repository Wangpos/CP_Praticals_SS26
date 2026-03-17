#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	int N;
	cin >> N;

	vector<int> numbers(N);
	for (int i = 0; i < N; i++) {
		cin >> numbers[i];
	}

	sort(numbers.begin(), numbers.end());

	numbers.erase(unique(numbers.begin(), numbers.end()), numbers.end());

	for (size_t i = 0; i < numbers.size(); i++) {
		cout << numbers[i];
		if (i + 1 < numbers.size()) {
			cout << " ";
		}
	}

	return 0;
}
