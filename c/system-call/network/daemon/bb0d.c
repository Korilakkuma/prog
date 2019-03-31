#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <fcntl.h>

#include "bb.h"

extern void service(int soc, char *myname);

int main(int argc, char **argv) {
    struct sockaddr_in me;

    int soc_waiting;
    int soc;

    pid_t pid;

    memset((char *)&me, 0, sizeof(me));

    me.sin_family = AF_INET;
    me.sin_addr.s_addr = htonl(INADDR_ANY);
    me.sin_port = htons(PORT);

    if ((soc_waiting = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    if (bind(soc_waiting, (struct sockaddr *)&me, sizeof(me)) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if (listen(soc_waiting, 5)) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (1) {
        if ((soc = accept(soc_waiting, NULL, NULL)) == -1) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        if ((pid = fork()) == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (pid == (pid_t)0) {
            if (close(soc_waiting) == -1) {
                perror("close");
                exit(EXIT_FAILURE);
            }

            service(soc, argv[0]);
            exit(EXIT_SUCCESS);
        } else {
            if (close(soc) == -1) {
                perror("close");
                exit(EXIT_FAILURE);
            }
        }

        printf("My child [%d] now serving ...\n", (int)pid);
    }
}
