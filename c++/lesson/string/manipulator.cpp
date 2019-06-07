#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

int main() {
    int n = 527;

    cout << '[' << setw(5) << n << ']' << endl;
    cout << '[' << n << ']' << endl;

    double x = 1.0 / 7;

    cout << x << endl;
    cout << setprecision(10);
    cout << x << endl;
    cout << setprecision(6);
}
