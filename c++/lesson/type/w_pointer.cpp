#include <iostream>

using namespace std;

int main() {
    int a = 10;
    int *p_a = &a;
    int **pp_a = &p_a;

    cout << **pp_a << endl;
}
