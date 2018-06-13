#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int fd;

    if (argc != 2) {
        fprintf(stderr, "Require argument\n");
        exit(1);
    }

    if ((fd = open(argv[1], (O_WRONLY | O_CREAT | O_TRUNC), 0666)) == -1) {
        perror("open");
        exit(1);
    }

    if (close(fd) == -1) {
        perror("close");
        exit(1);
    }

    return 0;
}
