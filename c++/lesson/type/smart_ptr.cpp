#include <iostream>
#include <complex>
#include <memory>

using namespace std;

int main() {
    using cplx = complex<double>;

    shared_ptr<cplx> p = make_shared<cplx>();
    // auto p = make_shared<cplx>();

    cout << "p: " << *p << endl;

    shared_ptr<cplx> q = make_shared<cplx>(3.0, 4.0);

    cout << "q: " << *q << endl;

    shared_ptr<cplx> r = make_shared<cplx>(*q);

    cout << "r: " << *r << endl;

    // Unnecessary `delete`
}
