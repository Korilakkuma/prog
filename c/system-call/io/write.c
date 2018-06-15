#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int fd;

    if (argc != 3) {
        fprintf(stderr, "Require 2 arguments\n");
        exit(1);
    }

    if ((fd = open(argv[1], (O_WRONLY | O_CREAT | O_TRUNC))) == -1) {
        perror("open");
        exit(1);
    }

    if (write(fd, argv[2], strlen(argv[2])) != strlen(argv[2])) {
        perror("write");
        exit(1);
    }

    if (close(fd) == -1) {
        perror("close");
        exit(1);
    }

    return 0;
}
