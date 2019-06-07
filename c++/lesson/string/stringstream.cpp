#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

int main() {
    stringstream ss;

    int n = 527;

    ss << "[" << setw(5) << n << "]" << endl;

    string result = ss.str();

    cout << result << endl;
}
