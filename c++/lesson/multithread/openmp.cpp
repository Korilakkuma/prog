#include <vector>
#include <algorithm>
#include <chrono>
#include "number.h"

using namespace std;
using namespace std::chrono;

int main() {
    auto t0 = high_resolution_clock::now();

    const int N = 400000;

    vector<int> primes;

    #pragma omp parallel
    #pragma omp for schedule(dynamic, 1000)
    for (int n = 2; n <= N; n++) {
        if (isPrime(n)) {
            #pragma omp critical
            primes.push_back(n);
        }
    }

    cout << "The number of primes: " << primes.size() << endl;

    sort(primes.begin(), primes.end());

    report(primes.cbegin(), primes.cend());

    auto t1 = high_resolution_clock::now();

    cout << (duration_cast<milliseconds>(t1 - t0).count() / 1000.0) << " sec" << endl;
}
