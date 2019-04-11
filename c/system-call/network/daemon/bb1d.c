#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <syslog.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>

#include "bb.h"

extern void service(int soc, char *myname);

static void ending(int sig) {
    syslog(LOG_ERR, "service terminated");
    closelog();
    exit(EXIT_SUCCESS);
}

int main(int argc, char **argv) {
    struct sockaddr_in me;
    int soc_waiting;
    int soc;
    pid_t pid;

    if (argc != 2) {
        fputs("Require 1 argument\n", stderr);
        exit(EXIT_FAILURE);
    }

    if ((pid = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid != 0) {
        // Child process is not process group leader
        exit(EXIT_SUCCESS);
    }

    if (setsid() == -1) {
        perror("setsid");
        exit(EXIT_FAILURE);
    }

    /*
    if ((pid = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid != 0) {
        exit(EXIT_FAILURE);
    }
    */

    if (chdir("/") == -1) {
        perror("chdir");
        exit(EXIT_FAILURE);
    }

    openlog(argv[0], LOG_PID, LOG_USER);

    if (close(STDIN_FILENO) == -1) {
        syslog(LOG_ERR, "close failed");
        exit(EXIT_FAILURE);
    }

    if (close(STDOUT_FILENO) == -1) {
        syslog(LOG_ERR, "close failed");
        exit(EXIT_FAILURE);
    }

    if (close(STDERR_FILENO) == -1) {
        syslog(LOG_ERR, "close failed");
        exit(EXIT_FAILURE);
    }

    signal(SIGTERM, ending);

    memset((char *)&me, 0, sizeof(me));

    me.sin_family = AF_INET;
    me.sin_addr.s_addr = htonl(INADDR_ANY);
    me.sin_port = htons(PORT);

    if ((soc_waiting = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        syslog(LOG_ERR, "socket failed");
        exit(EXIT_FAILURE);
    }

    if (bind(soc_waiting, (struct sockaddr *)&me, sizeof(me)) == -1) {
        syslog(LOG_ERR, "bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(soc_waiting, 5)) {
        syslog(LOG_ERR, "listen failed");
        exit(EXIT_FAILURE);
    }

    while (1) {
        if ((soc = accept(soc_waiting, NULL, NULL)) == -1) {
            syslog(LOG_ERR, "accept failed");
            exit(EXIT_FAILURE);
        }

        if ((pid = fork()) == -1) {
            syslog(LOG_ERR, "fork failed");
            exit(EXIT_FAILURE);
        } else if (pid == (pid_t)0) {
            if (close(soc_waiting) == -1) {
                syslog(LOG_ERR, "close failed");
            }

            service(soc, argv[0]);

            exit(EXIT_SUCCESS);
        } else {
            if (close(soc) == -1) {
                syslog(LOG_ERR, "close failed");
            }
        }
    }
}
