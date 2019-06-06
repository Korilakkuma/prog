#include <iostream>
#include <map>
#include <random>

using namespace std;

int main() {
    random_device engine;
    normal_distribution<double> dist(50.0, 5.0);

    map<int, int> frequency;

    for (int i = 0; i < 500; i++) {
        double x = dist(engine);
        frequency[static_cast<int>(x)]++;
    }

    for (auto p : frequency) {
        cout << p.first << " | ";

        for (int i = 0; i < p.second; i++) {
            cout << "*";
        }

        cout << endl;
    }
}
