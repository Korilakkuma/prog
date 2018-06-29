#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    char *name;
    char *value;

    if (argc != 3) {
        fprintf(stderr, "Require 2 arguments\n");
        exit(1);
    }

    name  = argv[1];
    value = argv[2];

    printf("%s is %s\n", name, getenv(name));

    if (setenv(name, value, 1) == -1) {
        perror("setenv");
        exit(1);
    }

    printf("%s is now %s\n", name, getenv(name));

    return 0;
}
