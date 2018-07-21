#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc < 3) {
        fputs("Require 2 arguments at least\n", stderr);
        exit(EXIT_FAILURE);
    }

    if (strncmp(argv[1], "-s", 2) == 0) {
        if (argc != 4) {
            fputs("Require 3 arguments\n", stderr);
            exit(EXIT_FAILURE);
        }

        if (symlink(argv[2], argv[3]) == -1) {
            perror("symlink");
            exit(EXIT_FAILURE);
        }
    } else {
        if (link(argv[1], argv[2]) == -1) {
            perror("link");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
