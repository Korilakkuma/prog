#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    pid_t pid;
    int c;

    if ((pid = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        c = 'C';
    } else {
        setpgid(pid, pid);
        tcsetpgrp(STDIN_FILENO, pid);

        c = 'P';
    }

    while (1) {
        fprintf(stderr, "%c", c);
        sleep(1);
    }

    return 0;
}
