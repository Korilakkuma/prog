#include <iostream>

using namespace std;

auto f() {
    int *a = new int[4] { 2, 3, 5, 7 };
    return a;
}

int main() {
    auto a = f();

    for (size_t i = 0; i < 4; i++) {
        cout << a[i] << endl;
    }

    delete[] a;
}
