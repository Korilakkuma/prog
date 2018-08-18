#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void alarm_handler(int sig) {
    // Noop
}

static void msleep(int sec) {
    sigset_t new_sigset;
    sigset_t old_sigset;

    sigaddset(&new_sigset, SIGALRM);

    signal(SIGALRM, alarm_handler);

    sigprocmask(SIG_BLOCK, &new_sigset, &old_sigset);

    alarm(sec);

    sigsuspend(&old_sigset);

    sigprocmask(SIG_SETMASK, &old_sigset, NULL);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fputs("Require 1 argument\n", stderr);
        exit(EXIT_FAILURE);
    }

    msleep((int)strtol(argv[1], NULL, 10));

    return 0;
}
