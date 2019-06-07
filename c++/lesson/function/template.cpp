#include <iostream>
#include <string>

using namespace std;

template <typename T>

void swap_by_ref(T &a, T &b);

int main() {
    int a = 1;
    int b = 2;

    swap_by_ref(a, b);

    cout << a << endl;
    cout << b << endl;

    double x = 1.1;
    double y = 2.2;

    swap_by_ref(x, y);

    cout << x << endl;
    cout << y << endl;

    string s = "abc";
    string t = "xyz";

    swap_by_ref(s, t);

    cout << s << endl;
    cout << t << endl;
}

template <typename T>

void swap_by_ref(T &a, T &b) {
    T tmp = a;
    a = b;
    b = tmp;
}
