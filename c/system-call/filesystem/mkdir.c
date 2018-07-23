#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        fputs("Require 1 argument\n", stderr);
        exit(EXIT_FAILURE);
    }

    if (mkdir(argv[1], 0777) == -1) {
        perror("mkdir");
        exit(EXIT_FAILURE);
    }

    return 0;
}
