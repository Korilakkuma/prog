#include <iostream>

using namespace std;

void f1(int *a, size_t s) {
    for (size_t i = 0; i < s; i++) {
        cout << a[i] << endl;
    }
}

void f2(int *first, int *last){
    for (int *p = first; p != last; p++) {
        cout << *p << endl;
    }
}
int main() {
    int a[] = { 2, 3, 5, 7 };

    size_t s = end(a) - begin(a);

    f1(a, s);
    f2(a, end(a));
}
