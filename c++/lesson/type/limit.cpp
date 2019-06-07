#include <iostream>
#include <limits>

using namespace std;

int main() {
    cout << "int minimum: " << numeric_limits<int>::lowest() << endl;
    cout << "int maximum: " << numeric_limits<int>::max() << endl;
}
