#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<int> v1{ 2, 3, 5, 7 };

    auto v2(v1);  // or auto v2 = v1;

    v1[0] = 100;

    for (auto x : v2) {
        cout << x << endl;
    }
}
