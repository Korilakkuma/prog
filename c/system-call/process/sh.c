#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include "../utils/vec.h"

enum {
    MAX_ARGV = 100
};

void getcmd(char *cmd);

int main(void) {
    char cmd[1024];
    char *av[MAX_ARGV];
    int ac, status;
    pid_t cpid;

    while (1) {
        fputs("% ", stdout);
        getcmd(cmd);

        if (feof(stdin)) {
            exit(0);
        } else if (ferror(stdin)) {
            perror("getcmd");
            exit(1);
        }

        if ((ac = strtovec(cmd, av, MAX_ARGV)) > MAX_ARGV) {
            fputs("too many arguments\n", stderr);
            continue;
        }

        if (ac == 1) {
            continue;
        }

        if ((cpid = fork()) == -1) {
            perror("fork");
            continue;
        } else if (cpid == 0) {
            execvp(av[0], av);
            perror(cmd);
            exit(1);
        } else {
            if (wait(&status) == (pid_t)-1) {
                perror("wait");
                exit(1);
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
        cmd[len + 1] = '\0';
    } else {
        *p = '\0';
    }
}
