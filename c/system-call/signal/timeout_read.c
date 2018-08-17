#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

static void alarm_handler(int sig) {
    // Noop
}

ssize_t timeout_read(int fd, void *buf, size_t count, int seconds) {
    ssize_t size;
    struct sigaction act;

    act.sa_handler = alarm_handler;
    act.sa_flags   = 0;

    sigemptyset(&act.sa_mask);

    sigaction(SIGALRM, &act, NULL);

    alarm(seconds);

    if ((size = read(STDIN_FILENO, buf, count)) == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    alarm(0);

    return size;
}

int main(int argc, char **argv) {
    char buf[1024];
    int seconds;
    ssize_t size;

    if (argc == 1) {
        seconds = 3;
    } else {
        seconds = (int)strtol(argv[1], NULL, 10);
    }

    printf("Type: ");
    fflush(stdout);

    if ((size = timeout_read(STDIN_FILENO, buf, sizeof(buf), seconds)) == -1) {
        fputs("Timed out\n", stderr);
    }

    write(STDOUT_FILENO, buf, size);

    return 0;
}
