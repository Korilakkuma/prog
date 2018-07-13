#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include "../utils/vec.h"

enum {
    MAX_ARGV = 100
};

void getcmd(char *cmd, size_t size);

int main(void) {
    char cmd[1024];
    char *av[MAX_ARGV];
    char *outfile;
    int ac;
    int status;
    int bg;
    int i;
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

        getcmd(cmd, sizeof(cmd));

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

        outfile = NULL;

        for (i = 0; i < ac; i++) {
            if (!strcmp(av[i], ">")) {
                av[i] = NULL;
                ac = i;
                outfile = av[i + 1];
                break;
            }
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
            if (outfile != NULL) {
                close(STDOUT_FILENO);

                if (open(outfile, (O_WRONLY | O_CREAT | O_TRUNC), 0666) == -1) {
                    perror("open");
                    exit(1);
                }
            }

            execvp(av[0], av);
            perror(cmd);
            exit(1);
        } else {
            if (!bg) {
                if (waitpid(cpid, &status, 0) == (pid_t)-1) {
                    perror("waitpid");
                    exit(1);
                }

                fprintf(stderr, "process %d finished\n", cpid);
            }
        }
    }

    exit(0);
}

void getcmd(char *cmd, size_t size) {
    int len;
    char *p;

    fgets(cmd, size, stdin);

    len = strlen(cmd) + 1;

    if ((p = strchr(cmd, '\n')) == NULL) {
        cmd[len - 1] = '\0';
    } else {
        *p = '\0';
    }
}
