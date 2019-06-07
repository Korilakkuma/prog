#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> v{ 1, 2, 3, 4, 5 };

    for (auto i = v.cbegin(); i != v.cend(); i++) {
        cout << *i << ", ";
    }

    cout << endl;

    for (auto i = v.begin(); i != v.end(); i++) {
        cout << (*i * 10) << ", ";
    }

    cout << endl;

    for (auto i = v.crbegin(); i != v.crend(); i++) {
        cout << *i << ", ";
    }

    cout << endl;

    for (auto i = v.rbegin(); i != v.rend(); i++) {
        cout << (*i * 10) << ", ";
    }

    cout << endl;
}
