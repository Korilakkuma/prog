#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> v;

    v.reserve(100);

    for (int i = 0; i < 100; i++) {
        cout << v.capacity() << ", ";
        v.push_back(i);
    }

    cout << endl;
}
