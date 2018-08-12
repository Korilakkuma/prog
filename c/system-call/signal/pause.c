#include <signal.h>
#include <stdio.h>
#include <unistd.h>

static void handler(int sig) {
    fprintf(stderr, "handler\n");
}

int main(void) {
    signal(SIGINT, handler);
    pause();
    fprintf(stderr, "Receive signal %d\n", SIGINT);
}
