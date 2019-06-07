#include <iostream>
#include <vector>
#include <complex>

using namespace std;

int main() {
    using cplx = complex<double>;

    vector<cplx> v;

    v.emplace_back(1.1, 2.2);
    v.emplace_back(3.3, 4.4);
    v.emplace_back(5.5, 6.6);
    v.emplace_back(7.7, 8.8);

    for (auto x : v) {
        cout << "real: " << x.real() << " imag: " << x.imag() << endl;
    }
}
