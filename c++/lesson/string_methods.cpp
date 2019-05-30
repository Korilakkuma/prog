#include <iostream>
#include <string>

using namespace std;

int main() {
    string str1 = "Hello, ";
    string str2 = "World!";

    cout << str1[4] << endl;

    str1 += str2;

    cout << str1 << endl;

    cout << (str1 == str2) << endl;
    cout << str1.compare("Hello, Z!") << endl;

    cout << str1.find("World") << endl;

    if (str1.find("world") == string::npos) {
        cout << "Not Found" << endl;
    }

    cout << str1.rfind("o") << endl;

    str1.replace(7, 5, "Japan");

    cout << str1 << endl;

    cout << str1.substr(7, 6) << endl;
}
