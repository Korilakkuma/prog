#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    vector<int> v{ 2, 3, 5, 1, 4 };

    auto begin = v.cbegin();
    auto end   = v.cend();

    int target = 3;

    auto p = find(begin, end, target);

    if (p == end) {
        cout << "Not Found" << endl;
    } else {
        cout << *p << endl;
    }

    target = 6;

    p = find(begin, end, target);

    if (p == end) {
        cout << "Not Found" << endl;
    } else {
        cout << *p << endl;
    }
}
