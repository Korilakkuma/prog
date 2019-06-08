#include <iostream>

using namespace std;

[[noreturn]]
void dosomething() {
    throw runtime_error("error");
}

int main() {
    try {
        dosomething();
    } catch (exception &e) {
        cerr << e.what() << endl;
    }
}
