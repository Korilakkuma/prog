#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include "../utils/getcmd.h"
#include "../utils/vec.h"

enum {
    MAX_ARGV = 100
};

int main(void) {
    char cmd[1024];
    char *userinput[MAX_ARGV];
    char *av[MAX_ARGV];
    char *infile;
    char *outfile;
    int i;
    int nwords;
    int ac;
    int status;
    pid_t cpid;

    while (1) {
        fputs("% ", stdout);

        getcmd(cmd, sizeof(cmd));

        if (feof(stdin)) {
            exit(EXIT_SUCCESS);
        } else if (ferror(stdin)) {
            perror("cmd");
            exit(EXIT_FAILURE);
        }

        if ((nwords = strtovec(cmd, userinput, MAX_ARGV)) > MAX_ARGV) {
            fputs("too many arguments\n", stderr);
            continue;
        }

        nwords--;

        if (nwords == 0) {
            continue;
        }

        ac = 0;

        infile = NULL;
        outfile = NULL;

        for (i = 0; i < nwords; i++) {
            if (strcmp(userinput[i], ">") == 0) {
                outfile = userinput[i + 1];
                i++;
            } else if (strcmp(userinput[i], "<") == 0) {
                infile = userinput[i + 1];
                i++;
            } else {
                av[ac++] = userinput[i];
            }
        }

        av[ac] = NULL;

        if ((cpid = fork()) == -1) {
            perror("fork");
            continue;
        } else if (cpid == 0) {
            if (infile != NULL) {
                close(STDIN_FILENO);

                if (open(infile, O_RDONLY) == -1) {
                    perror(infile);
                    exit(EXIT_FAILURE);
                }
            }

            if (outfile != NULL) {
                close(STDOUT_FILENO);

                if (open(outfile, (O_WRONLY | O_CREAT | O_TRUNC), 0666) == -1) {
                    perror(outfile);
                    exit(EXIT_FAILURE);
                }
            }

            execvp(av[0], av);
            perror(cmd);
            exit(EXIT_FAILURE);
        } else {
            if (wait(&status) == (pid_t)-1) {
                perror("wait");
                exit(EXIT_FAILURE);
            }
        }
    }

    exit(EXIT_SUCCESS);
}
