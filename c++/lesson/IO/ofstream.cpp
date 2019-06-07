#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    ofstream outfile("./sample.txt", ios_base::app);
    string in;

    while (cin >> in) {
        outfile << in << endl;
    }

    outfile.close();
}
