#include <iostream>
#include <complex>

using namespace std;
using cplx = complex<double>;

int main() {
    cplx a;
    // cplx a{};

    cout << "a: " << a << endl;

    cplx b(3.0, 4.0);
    // cplx b{3.0, 4.0};

    cout << "b: " << b << endl;

    cplx c(b);
    // cplx c{ b };
    // cplx c = b;

    cout << "c: " << c << endl;

    cout << "real: " << b.real() << endl;
    cout << "imag: " << b.imag() << endl;
}
