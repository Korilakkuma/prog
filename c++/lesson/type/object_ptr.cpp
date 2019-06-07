#include <iostream>
#include <complex>

using namespace std;
using cplx = complex<double>;

int main() {
    cplx *p = new cplx;
    // cplx *p = new cplx();
    // cplx *p = new cplx{};

    cout << "p: " << *p << endl;

    cplx *q = new cplx(3.0, 4.0);
    // cplx *q = new cplx{3.0, 4.0};

    cout << "q: " << *q << endl;

    cplx *r = new cplx(*q);
    // cplx *r = new cplx{ *q };

    cout << "real: " << q->real() << endl;
    cout << "imag: " << q->imag() << endl;

    delete p;
    delete q;
    delete r;
}
