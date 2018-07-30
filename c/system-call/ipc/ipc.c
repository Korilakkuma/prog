#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv) {
    int fd[2];
    int nbytes;
    int status;
    char buf[1024];
    pid_t pid;

    if (argc != 2) {
        fputs("Require 1 argument\n", stderr);
        exit(EXIT_FAILURE);
    }

    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    if ((pid = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        close(fd[1]);
        nbytes = read(fd[0], buf, sizeof(buf));
        write(STDOUT_FILENO, buf, nbytes);
        close(fd[0]);
    } else {
        close(fd[0]);
        write(fd[1], argv[1], strlen(argv[1]));
        close(fd[1]);

        waitpid(pid, &status, 0);
    }

    return 0;
}
