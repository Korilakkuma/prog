#include <stdio.h>

int main(void) {
    int c;

    while ((c = fgetc(stdin)) != EOF) {
        putchar(c);
    }

    return 0;
}
