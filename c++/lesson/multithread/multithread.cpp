#include <thread>
#include <mutex>
#include <vector>
#include <algorithm>
#include <chrono>
#include "number.h"

using namespace std;
using namespace std::chrono;

mutex m;
vector<int> primes;

void threadFunc(int N, int start) {
    for (int n = start; n < N; n += 3) {
        if (isPrime(n)) {
            unique_lock<mutex> lock(m);
            primes.push_back(n);
        }
    }
}

int main() {
    auto t0 = high_resolution_clock::now();

    const int N = 400000;

    primes.push_back(2);
    primes.push_back(3);

    thread threadA(threadFunc, N, 4);
    thread threadB(threadFunc, N, 5);

    threadA.join();
    threadB.join();

    cout << "The number of primes: " << primes.size() << endl;

    sort(primes.begin(), primes.end());

    report(primes.cbegin(), primes.cend());

    auto t1 = high_resolution_clock::now();

    cout << (duration_cast<milliseconds>(t1 - t0).count() / 1000.0) << " sec" << endl;
}
