#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#include "bb.h"

void session(int soc) {
    int width;
    fd_set mask;
    char buf[BUF_LENGTH];

    FD_ZERO(&mask);
    FD_SET(STDIN_FILENO, &mask);
    FD_SET(soc, &mask);

    width = soc + 1;

    while (1) {
        int cnt;
        fd_set read0k;

        read0k = mask;

        if (select(width, &read0k, NULL, NULL, NULL) == -1) {
            perror("select");
            exit(EXIT_FAILURE);
        }

        if (FD_ISSET(soc, (fd_set *)&read0k)) {
            if ((cnt = read(soc, buf, BUF_LENGTH)) == -1) {
                perror("read");
                exit(EXIT_FAILURE);
            }

            if (write(STDOUT_FILENO, buf, cnt) == -1) {
                perror("write");
                exit(EXIT_FAILURE);
            }
        }

        if (FD_ISSET(STDIN_FILENO, (fd_set *)&read0k)) {
            if ((cnt = read(STDIN_FILENO, buf, BUF_LENGTH)) == -1) {
                perror("read");
                exit(EXIT_FAILURE);
            }

            if (write(soc, buf, cnt) == -1) {
                perror("write");
                exit(EXIT_FAILURE);
            }

            if (buf[0] == '9') {
                exit(EXIT_SUCCESS);
            }
        }
    }
}
