#include <iostream>

using namespace std;

int main() {
    int a = 10;
    int &b = a;

    b = 15;

    cout << a << endl;
}
