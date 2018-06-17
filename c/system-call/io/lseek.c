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

    if (argc != 4) {
        fprintf(stderr, "Require 3 arguments (filename, offset, string)\n");
        exit(1);
    }

    if ((fd = open(argv[1], O_WRONLY)) == -1) {
        perror("open");
        exit(1);
    }

    if (lseek(fd, strtol(argv[2], NULL, 10), SEEK_SET) == -1) {
        perror("lseek");
        exit(1);
    }

    if (write(fd, argv[3], strlen(argv[3])) != strlen(argv[3])) {
        perror("write");
        exit(1);
    }

    if (close(fd) == -1) {
        perror("close");
        exit(1);
    }

    return 0;
}
