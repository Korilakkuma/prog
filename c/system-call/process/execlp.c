#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Require 2 arguments\n");
        exit(EXIT_FAILURE);
    }

    char *file = argv[1];
    char *arg  = argv[2];

    printf("Invoking %s\n", file);

    execlp(file, file, arg, (char *)0);

    printf("Done\n");

    return 0;
}
