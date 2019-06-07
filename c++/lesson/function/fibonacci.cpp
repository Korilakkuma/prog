#include <iostream>

using namespace std;

int fibonacci(int n);

int main() {
    for (int n = 1; n <= 10; ++n) {
        cout << "f(" << n << ") = " << fibonacci(n) << endl;
    }
}

int fibonacci(int n) {
    if (n < 3) {
        return 1;
    }

    return fibonacci(n - 1) + fibonacci(n - 2);
}
