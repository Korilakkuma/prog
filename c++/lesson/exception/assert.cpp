#include <iostream>
#include <cassert>

using namespace std;

int main() {
    int low  = 0;
    int mid  = 10;
    int high = 5;

    assert((low <= mid) && (mid <= high));

    cout << "assert" << endl;
}
