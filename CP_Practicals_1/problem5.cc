#include <iostream>
#include <deque>
#include <string>

using namespace std;

void printLine(const deque<int>& dq) {
    for (size_t i = 0; i < dq.size(); i++) {
        cout << dq[i];
        if (i + 1 < dq.size()) cout << " ";
    }
    cout << "\n";
}

int main() {
    int Q;
    cin >> Q;

    deque<int> line;

    while (Q--) {
        string op;
        cin >> op;

        if (op == "push_front") {
            int x;
            cin >> x;
            line.push_front(x);
        } else if (op == "push_back") {
            int x;
            cin >> x;
            line.push_back(x);
        } else if (op == "pop_front") {
            if (!line.empty()) line.pop_front();
        } else if (op == "pop_back") {
            if (!line.empty()) line.pop_back();
        }

        printLine(line);
    }

    return 0;
}
