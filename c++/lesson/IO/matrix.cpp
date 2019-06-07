#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

int main() {
    ifstream datafile("./test.dat");
    regex rx(R"(\s)");
    string str;

    while (getline(datafile, str)) {
        sregex_token_iterator it(str.begin(), str.end(), rx, -1);
        sregex_token_iterator end;

        string label = *it++;

        int total = 0;

        while (it != end) {
            total += stoi(*it++);
        }

        cout << label << ": " << total << endl;
    }

    datafile.close();
}
