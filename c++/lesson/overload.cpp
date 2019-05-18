#include <iostream>

using namespace std;

void swap_by_ref(int &a, int &b);
void swap_by_ref(double &a, double &b);

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
}


void swap_by_ref(int &a, int &b) {
    int tmp = a;
    a = b;
    b = tmp;
}

void swap_by_ref(double &a, double &b) {
    double tmp = a;
    a = b;
    b = tmp;
}
