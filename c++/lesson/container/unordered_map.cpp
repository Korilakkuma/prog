#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

int main() {
    unordered_map<string, int> dictionary{ { "one", 0 }, { "two", 2 }, { "three", 3 } };

    cout << dictionary["two"] << endl;

    cout << dictionary["one"] << endl;

    dictionary["one"] = 1;

    cout << dictionary["one"] << endl;

    cout << dictionary["four"] << endl;

    if (dictionary.find("five") == dictionary.end()) {
        cout << "Not Found" << endl;
    }

    if (dictionary.find("four") == dictionary.end()) {
        cout << "Not Found" << endl;
    } else {
        cout << "Found: " << dictionary["four"] << endl;
    }

    dictionary["six"] = 6;

    for (const auto &p : dictionary) {
        cout << p.first << ": " << p.second << endl;
    }
}
