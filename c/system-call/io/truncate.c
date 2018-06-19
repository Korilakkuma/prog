#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Require 2 arguments\n");
        exit(1);
    }

    char *file = argv[1];
    off_t offset = (off_t)strtol(argv[2], NULL, 10);

    if (truncate(file, offset) == -1) {
        perror("truncate");
        exit(1);
    }

    return 0;
}
