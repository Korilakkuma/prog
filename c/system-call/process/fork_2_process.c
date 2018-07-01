#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    pid_t pid;

    if ((pid = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == 0) {
        printf("child: parent PID = %d, My PID = %d\n", getppid(), getpid());
        exit(EXIT_SUCCESS);
    } else {
        printf("parent: My PID = %d, child PID = %d\n", getpid(), pid);

        while (1) {
            sleep(1);
        }
    }
}
