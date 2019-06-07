#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int numberOfDivisors(int n);
bool less2(int lhs, int rhs);

int main() {
    cout << min(3, 2) << endl;
    cout << max(3, 2) << endl;

    cout << min({ 3, 2, 1, 4 }) << endl;
    cout << max({ 3, 2, 1, 4 }) << endl;

    auto r = minmax({ 3, 2, 1, 4 });

    cout << r.first << endl;
    cout << r.second << endl;

    auto d = minmax({ 10, 11, 9, 12 }, less2);

    cout << d.first << endl;
    cout << d.second << endl;

    vector<int> v{ 10, 11, 9, 12 };

    auto minIt    = min_element(v.cbegin(), v.cend());
    auto maxIt    = max_element(v.cbegin(), v.cend());
    // auto minmaxIt = minmax_element(v.cbegin(), v.end(), less2);

    cout << *minIt << endl;
    cout << *maxIt << endl;

    // cout << *minmaxIt.first << endl;
    // cout << *minmaxIt.second << endl;
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
