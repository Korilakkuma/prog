#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void alarm_handler(int sig) {
    // Noop
}

static void msleep(int sec) {
    signal(SIGALRM, alarm_handler);
    alarm(sec);
    pause();
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fputs("Require 1 argument\n", stderr);
        exit(EXIT_FAILURE);
    }

    msleep((int)strtol(argv[1], NULL, 10));

    return 0;
}
