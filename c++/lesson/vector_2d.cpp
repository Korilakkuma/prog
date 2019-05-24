#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<vector<int>> v{ { 1, 2, 3 }, { 4, 5, 6 } };

    cout << "Row; " << v.size() << endl;
    cout << "Col: " << v[0].size() << endl;

    for (const auto &r : v) {
        for (const auto &c : r) {
            cout << c << ", ";
        }

        cout << endl;
    }
}
