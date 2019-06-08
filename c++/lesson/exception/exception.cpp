#include <iostream>

using namespace std;

int main() {
    try {
        while (true) {
            int *p = new int[0x1fffffff];

            cout << p << endl;
        }
    } catch (bad_alloc &e) {
        cerr << e.what() << endl;
    }
}
