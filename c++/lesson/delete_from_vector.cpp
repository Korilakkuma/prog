#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> v{ 2, 3, 5, 7 };

    v.pop_back();

    for (auto x : v) {
        cout << x << endl;
    }

    v.erase(v.begin() + 1);

    for (auto x : v) {
        cout << x << endl;
    }
}
