#include <iostream>
#include <algorithm>
using namespace std;

int main() {
     int N[] = {10, 12, 14, 16, 18, 20};
     cout << *max_element(N, N + 6) << endl;
     cout << *min_element(N, N + 6) << endl;
     return 0;
}