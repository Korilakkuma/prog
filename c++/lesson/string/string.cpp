#include <iostream>
#include <string>

using namespace std;

int main() {
    string str1 = "Hello";
    string str2;

    cout << str1 << endl;

    str2 = str1;

    cout << str2 << endl;

    str2 = str1 + " World";

    cout << str2 << endl;

    cout << (str1 + str2) << endl;
}
