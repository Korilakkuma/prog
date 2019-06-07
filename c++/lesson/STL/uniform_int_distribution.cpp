#include <iostream>
#include <random>

using namespace std;

int main() {
    random_device engine;
    uniform_int_distribution<unsigned> dist(1, 6);

    for (int i = 0; i < 10; i++) {
        cout << dist(engine) << ", ";
    }

    cout << endl;
}
