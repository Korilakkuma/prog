#include <iostream>
#include <chrono>
#include <unistd.h>

using namespace std;
using namespace std::chrono;

int main() {
    auto t0 = high_resolution_clock::now();

    int s = 0;

    for (int i = 0; i < 10; i++) {
        s++;
        sleep(1);
    }

    auto t1 = high_resolution_clock::now();

    cout << (duration_cast<milliseconds>(t1 - t0).count() / 1000.0) << "s" << endl;
}
