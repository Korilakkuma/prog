#include <iostream>
#include <cfenv>

using namespace std;

void report_fexcepts() {
    if (fetestexcept(FE_DIVBYZERO)) cout << "FE_DIVBYZERO" << endl;
    if (fetestexcept(FE_INEXACT))   cout << "FE_INEXACT" << endl;
    if (fetestexcept(FE_OVERFLOW))  cout << "FE_OVERFLOW" << endl;
    if (fetestexcept(FE_UNDERFLOW)) cout << "FE_UNDERFLOW" << endl;
    if (fetestexcept(FE_INVALID))   cout << "FE_INVALID" << endl;
    feclearexcept(FE_ALL_EXCEPT);
}

int main() {
    double d;
    // float f;

    d = 0;

    cout << 1.0 / d << endl;

    report_fexcepts();
}
