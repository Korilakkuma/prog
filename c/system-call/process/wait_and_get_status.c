#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>

void getcmd(char *cmd);

int main(void) {
    char cmd[1024];
    int status;
    pid_t pid;

    while (1) {
        fputs("% ", stdout);
        getcmd(cmd);

        if ((pid = fork()) == -1) {
            perror("fork");
            exit(1);
        } else if (pid == 0) {
            execlp(cmd, cmd, (char *)0);
            perror(cmd);
            exit(1);
        } else {
            if (wait(&status) == (pid_t)-1) {
                perror("wait");
                exit(1);
            }

            if (WIFEXITED(status)) {
                printf("Exit %d\n", WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {
                printf("Exit by signal %d\n", WTERMSIG(status));
            }
        }
    }

    exit(0);
}

void getcmd(char *cmd) {
    int len;
    char *p;

    fgets(cmd, sizeof(cmd), stdin);

    len = strlen(cmd) + 1;

    if ((p = strchr(cmd, '\n')) == NULL) {
        cmd[len - 1] = '\0';
    } else {
        *p = '\0';
    }
}
