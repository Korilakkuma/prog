#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Require 1 argument at least\n");
        exit(1);
    }

    if (chdir(argv[1]) == -1) {
        perror("chdir");
        exit(1);
    }

    execvp(argv[2], &argv[2]);

    perror("exec");
    exit(1);
}
