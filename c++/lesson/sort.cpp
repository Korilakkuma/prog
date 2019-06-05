#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<int> v{ 2, 3, 5, 1, 4 };

    sort(v.begin(), v.end());

    for (auto i : v) {
        cout << i << ", ";
    }

    cout << endl;

    int a[] = { 2, 3, 5, 1, 4 };

    sort(begin(a), end(a));

    for (auto i : a) {
        cout << i << ", ";
    }

    cout << endl;
}
