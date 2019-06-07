#include <iostream>
#include <string>
#include <regex>

using namespace std;

int main() {
    regex rx(R"XXX(\d{3}-\d{4})XXX");

    string zip = "153-0042";

    if (regex_match(zip, rx)) {
        cout << "OK" << endl;
    } else {
        cout << "NG" << endl;
    }

    zip = "154-00134";

    if (regex_match(zip, rx)) {
        cout << "OK" << endl;
    } else {
        cout << "NG" << endl;
    }
}
