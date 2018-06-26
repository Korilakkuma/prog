#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    pid_t pid;
    char command[1024];

    pid = getpid();

    printf("pid = %d\n", pid);

    if (snprintf(command, sizeof(command), "ps -l -p %d", pid) >= sizeof(command)) {
        fprintf(stderr, "Too long command line (pid = %d)\n", pid);
        exit(1);
    }

    system(command);

    return 0;
}
