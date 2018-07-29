#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv) {
    int fd[2];
    int nbytes;
    char buf[1024];

    if (argc != 2) {
        fputs("Require 1 argument\n", stderr);
        exit(EXIT_FAILURE);
    }

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    write(fd[1], argv[1], strlen(argv[1]));
    nbytes = read(fd[0], buf, sizeof(buf));
    write(STDOUT_FILENO, buf, nbytes);

    close(fd[0]);
    close(fd[1]);

    return 0;
}
