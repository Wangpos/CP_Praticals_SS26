// #include <iostream>

// using namespace std;

// given the set: {'A', 'B', 'C'}, generate all subsets of the set

// int main() {
//     char set[] = {'A', 'B', 'C'};
//     int n = sizeof(set) / sizeof(set[0]);
//     int total_subsets = 1 << n; // 2^n subsets

//     for (int i = 0; i < total_subsets; i++) {
//         cout << "{ ";
//         for (int j = 0; j < n; j++) {
//             if (i & (1 << j)) { // check if the j-th element is included in the subset
//                 cout << set[j] << " ";
//             }
//         }
//         cout << "}" << endl;
//     }

//     return 0;
// }


// --------------------------
// #include <iostream>
// #include <vector>
// #include <string>
// using namespace std;

// int main() {
//      vector<string> toppings = {"Olive", "Mushrooms", "Onions", "pineapple"};
//      vector<int> prices = {5, 2, 3, 4};
//      int budget = 8;
//      int n = toppings.size();

//      cout << "Topping combinations within Rs " << budget << ":\n";

//      // Iterate over all 2^n masks
//      for (int mask = 0; mask < (1 << n); mask++) {
//           int total_price = 0;
//           vector<string> chosen_toppings;

//           // Check each bit of the mask
//           for (int i = 0; i < n; i++) {
//                if (mask & (1 << i)) { // Is the i-th topping included?
//                     total_price += prices[i];
//                     chosen_toppings.push_back(toppings[i]);
//                }
//           }

//           if (total_price <= budget && !chosen_toppings.empty()) {
//                cout << "  Combo: ";
//                for (const auto& t : chosen_toppings) cout << t << " ";
//                cout << "| Price: Rs " << total_price << endl;
//           }
//      }
//      return 0;
// }


