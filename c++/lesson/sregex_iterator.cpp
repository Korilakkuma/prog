#include <iostream>
#include <string>
#include <regex>

using namespace std;

int main() {
    string str ="My postal code is 194-0013, her postal code is 153-0042";

    regex rx(R"(\d{3}-\d{4})");

    sregex_iterator it(str.begin(), str.end(), rx);
    sregex_iterator end;

    while (it != end) {
        cout << (it++)->str() << endl;
    }
}
