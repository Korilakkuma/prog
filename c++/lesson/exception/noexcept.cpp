#include <iostream>
#include <vector>

using namespace std;

void dosomething() noexcept {
    vector<int> v{ 2, 3, 5 };
    cout << v.at(3) << endl;
}

int main() {
    try {
        dosomething();
    } catch (...) {
        cerr << "noexcept" << endl;
    }
}
