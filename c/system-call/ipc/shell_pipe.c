#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int fd[2];
    pid_t pid;

    if (argc != 3) {
        fputs("Require 2 arguments\n", stderr);
        exit(EXIT_FAILURE);
    }

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    if ((pid = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        dup2(fd[1], STDOUT_FILENO);

        close(fd[0]);
        close(fd[1]);

        execlp(argv[1], argv[1], (char *)NULL);

        perror("execlp");
        exit(EXIT_FAILURE);
    }

    dup2(fd[0], STDIN_FILENO);

    close(fd[0]);
    close(fd[1]);

    execlp(argv[2], argv[2], (char *)NULL);

    perror("execlp");
    exit(EXIT_FAILURE);
}
