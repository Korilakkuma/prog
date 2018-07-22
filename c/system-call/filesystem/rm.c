#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        fputs("Require 1 argument\n", stderr);
        exit(EXIT_FAILURE);
    }

    if (unlink(argv[1]) == -1) {
        perror("unlink");
        exit(EXIT_FAILURE);
    }

    return 0;
}
