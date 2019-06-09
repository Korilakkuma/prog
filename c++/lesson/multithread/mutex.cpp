#include <thread>
#include <mutex>
#include "number.h"

using namespace std;

const int N = 100;

mutex m;

void threadFunc(int N, int start) {
    for (int n = start; n < N; n += 3) {
        if (isPrime(n)) {
            unique_lock<mutex> lock(m);
            cout << n << ", ";
        }
    }
}

int main() {
    cout << "2, 3, ";

    thread threadA(threadFunc, N, 4);
    thread threadB(threadFunc, N, 5);

    threadA.join();
    threadB.join();

    cout << endl;
}
