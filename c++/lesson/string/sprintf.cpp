#include <iostream>
#include <cstdio>

using namespace std;

int main() {
    char str[100];

    int a = 10;
    int b = 20;

    sprintf(str, "%d + %d = %d", a, b, (a + b));

    cout << str << endl;
}
