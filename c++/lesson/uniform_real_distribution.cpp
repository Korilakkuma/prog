#include <iostream>
#include <random>

using namespace std;

int main() {
    random_device engine;
    uniform_real_distribution<double> dist(0.0, 1.0);

    for (int i = 0; i < 5; i++) {
        cout << dist(engine) << ", ";
    }

    cout << endl;
}
