#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int fd;

    if (argc < 3) {
        fputs("Require 2 arguments at least\n", stderr);
        exit(EXIT_FAILURE);
    }

    fd = open(argv[1], (O_WRONLY | O_CREAT | O_TRUNC), 0666);

    dup2(fd, STDOUT_FILENO);

    execvp(argv[2], &argv[2]);

    perror("execvp");
    exit(EXIT_FAILURE);
}
