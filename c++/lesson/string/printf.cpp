#include <cstdio>

int main() {
    int x = 10;
    double y = 3.1415926535;

    printf("Hello World !\n");
    printf("The value is %d.\n", x);
    printf("%d, %f\n", x, y);
    printf("<%5d>\n", x);
    printf("%.7f\n", y);
    printf("The address of x is %p.\n", static_cast<void *>(&x));
}
