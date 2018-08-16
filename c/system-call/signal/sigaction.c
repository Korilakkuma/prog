#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void handler(int sig) {
    fprintf(stderr, "@");
}

int main(int argc, char **argv) {
    struct sigaction act;
    int sig;

    if (argc == 1) {
        sig = SIGINT;
    } else {
        sig = (int)strtol(argv[1], NULL, 10);
    }

    act.sa_handler = handler;
    act.sa_flags   = 0;

    sigemptyset(&act.sa_mask);

    sigaction(sig, &act, NULL);

    while (1) {
        sleep(1);
        putchar('.');
        fflush(stdout);
    }
}
