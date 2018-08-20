#include <signal.h>
#include <stdio.h>

#define MAX 10000000

static volatile long long counter1 = 0;
static volatile long long counter2 = 0;

static void handler(int sig) {
    counter1++;
    counter2++;
}

int main(void) {
    sigset_t set;
    sigset_t oldset;

    long long i;

    signal(SIGINT, handler);

    for (i = 0; i < MAX; i++) {
        sigemptyset(&set);
        sigaddset(&set, SIGINT);
        sigprocmask(SIG_BLOCK, &set, &oldset);

        counter1++;

        sigprocmask(SIG_SETMASK, &oldset, NULL);
    }

    printf("counter1 = %lld\n", counter1);
    printf("counter2 = %lld\n", counter2);

    return 0;
}
