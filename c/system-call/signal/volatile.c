#include <signal.h>
#include <stdio.h>

#define MAX 1000000000

static volatile long long counter = 0;

static void handler(int sig) {
    printf("%lld\n", counter);
}

int main(void) {
    long long i;

    signal(SIGINT, handler);

    for (i = 0; i < MAX; i++) {
        counter++;
    }

    printf("counter = %lld\n", counter);

    return 0;
}
