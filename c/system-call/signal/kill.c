#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        fputs("Require process ID\n", stderr);
        exit(EXIT_FAILURE);
    }

    pid_t pid = (pid_t)strtol(argv[1], NULL, 10);

    kill(pid, SIGTERM);

    return 0;
}
