#include <iostream>

using namespace std;

void swap_by_ref(int &a, int &b);

int main() {
    int a = 1;
    int b = 2;

    swap_by_ref(a, b);

    cout << a << endl;
    cout << b << endl;
}

void swap_by_ref(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}
