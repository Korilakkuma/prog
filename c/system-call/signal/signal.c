#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void handler(int sig) {
    fprintf(stderr, "@");
}

int main(int argc, char **argv) {
    int sig;

    if (argc == 1) {
        sig = SIGINT;
    } else if (argc == 2) {
        sig = (int)strtol(argv[1], NULL, 10);
    } else {
        fputs("Too many arguments\n", stderr);
        exit(EXIT_FAILURE);
    }

    signal(sig, handler);

    while (1) {
        sleep(1);
        putchar('.');
        fflush(stdout);
    }

    return 0;
}
