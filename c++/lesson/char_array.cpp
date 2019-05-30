#include <iostream>
#include <cstring>

using namespace std;

void report(const char *cstr) {
    for (int i = 0; cstr[i] != '\0'; i++) {
        cout << '[' << i << ']' << cstr[i] << endl;
    }
}

int main() {
    char cstr[] = "hello";

    cstr[0] = 'H';

    cout << cstr << endl;

    size_t size = end(cstr) - begin(cstr);

    cout << size << endl;
    cout << strlen(cstr) << endl;

    report(cstr);
}
