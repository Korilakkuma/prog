#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    pid_t cpid;

    if ((cpid = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (cpid == 0) {
        sleep(3);
        printf("\nmy parent is now pid %d\n", getppid());
        exit(EXIT_SUCCESS);
    }

    printf("parent process, pid %d\n", getpid());
    exit(EXIT_SUCCESS);
}
