// Problem 2 — Reverse the Array
// Given N integers, print the array in reverse order.
// Example
// Input
// N= 5 and elements 1 2 3 4 5
// Output: 5 4 3 2 1
// Hint: Use vector and reverse traversal.

#include <iostream>
#include <vector>
using namespace std;
int main() {
     int N;
     cin >> N;

     vector<int> arr(N);
     for (int i = 0; i < N; i++) {
          cin >> arr[i];
     }

     for (int i = N - 1; i >= 0; i--) {
          cout << arr[i];
          if (i != 0) {
               cout << " ";
          }
     }
     cout << '\n';

     return 0;
}