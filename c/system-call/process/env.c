#include <stdio.h>

extern char **environ;

int main(void) {
    char **p = environ;

    while (*p != NULL) {
        printf("%s\n", *p);
        p++;
    }

    return 0;
}
