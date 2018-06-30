#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    int i = 2012;
    pid_t pid;

    pid = getpid();

    printf("Before fork: pid = %d, i = %d\n", pid, i);

    fflush(stdout);

    fork();

    pid = getpid();

    printf("After fork: pid = %d, i = %d\n", pid, i);

    sleep(1);

    exit(EXIT_SUCCESS);
}
