#include <iostream>
#include <string>

using namespace std;

int main() {
    int x = 56234;

    string strx = to_string(x);

    cout << strx << endl;
    cout << strx.size() << endl;

    double y = 2.716;

    string stry = to_string(y);

    cout << stry << endl;
    cout << stry.size() << endl;
}
