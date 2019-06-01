#include <iostream>

using namespace std;

int main() {
    string stri = "561";
    int i = stoi(stri);

    cout << (i + 1) << endl;

    string strd = "0.31415";
    double d = stod(strd);

    cout << (d * 10) << endl;
}
