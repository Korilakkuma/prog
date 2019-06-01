#include <iostream>

using namespace std;

int main() {
    cout << "Type number" << endl;

    int total = 0;
    int n;

    while (cin >> n) {
        total += n;
    }

    cout << "Total: " << total << endl;
}
