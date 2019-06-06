#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int numberOfDivisors(int n);
bool less2(int lhs, int rhs);

int main() {
    const int N = 16;

    vector<int> v;

    for (int i = 1; i <= N; i++) {
        v.push_back(i);
    }

    vector<int> v1 = v;

    sort(v1.begin(), v1.end(), less2);

    for (auto i : v1) {
        cout << i << ", ";
    }

    cout << endl;
}

int numberOfDivisors(int n) {
    int divisors = 0;

    for (int i = 1; i < n; i++) {
        if ((n % i) == 0) {
            divisors++;
        }
    }

    return divisors;
}

bool less2(int lhs, int rhs) {
    return numberOfDivisors(lhs) < numberOfDivisors(rhs);
}
