#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <unistd.h>

#define BUF_SIZE 1024

int main(int argc, char **argv) {
    int fd;
    ssize_t cc;
    char buf[BUF_SIZE];

    if (argc != 2) {
        fprintf(stderr, "Require 1 argumnet\n");
        exit(1);
    }

    if ((fd = open(argv[1], (O_WRONLY | O_CREAT | O_TRUNC), 0666)) == -1) {
        perror("open");
        exit(1);
    }

    while ((cc = read(STDIN_FILENO, buf, sizeof(buf))) > 0 ) {
        if (write(fd, buf, cc) != cc) {
            perror("write");
            exit(1);
        }
    }

    if (cc == -1) {
        perror("read");
        exit(1);
    }

    if (close(fd) == -1) {
        perror("close");
        exit(1);
    }

    return 0;
}
