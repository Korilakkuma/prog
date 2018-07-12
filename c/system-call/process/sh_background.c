#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "../utils/vec.h"

enum {
    MAX_ARGV = 100
};

void getcmd(char *cmd);

int main(void) {
    char cmd[1024];
    char *av[MAX_ARGV];
    int ac;
    int status;
    int bg;
    pid_t cpid;
    pid_t zpid;

    while (1) {
        while ((zpid = waitpid(-1, &status, WNOHANG)) > 0) {
            fprintf(stderr, "process %d salvaged\n", zpid);
        }

        if ((zpid == -1) && (errno != ECHILD)) {
            perror("waitpid(2)");
            exit(1);
        }

        fputs("% ", stdout);

        getcmd(cmd);

        if (feof(stdin)) {
            exit(0);
        } else if (ferror(stdin)) {
            perror("getcmd");
            exit(1);
        }

        if ((ac = strtovec(cmd, av, MAX_ARGV)) > MAX_ARGV) {
            fputs("argument list too long\0", stderr);
            continue;
        }

        ac--;

        if (ac == 0) {
            continue;
        }

        if (!strcmp(av[ac - 1], "&")) {
            av[ac - 1] = NULL;
            ac--;
            bg = 1;

            if (ac == 0) {
                fputs("invalid null command\n", stderr);
                continue;
            }
        } else {
            bg = 0;
        }

        if ((cpid = fork()) == -1) {
            perror("fork");
            exit(1);
        } else if (cpid == 0) {
            execvp(av[0], av);
            perror(av[0]);
            exit(1);
        } else {
            if (!bg) {
                if (waitpid(cpid, &status, 0) == (pid_t)-1) {
                    perror("waitpid(2)");
                    exit(1);
                }

                fprintf(stderr, "process %d finished\n", cpid);
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
