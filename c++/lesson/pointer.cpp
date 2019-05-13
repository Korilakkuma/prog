#include <iostream>

using namespace std;

int main() {
    int a = 10;
    int *p_a = &a;  // int *p_a = addressof(a);

    *p_a = 20;

    cout << a << endl;
}
