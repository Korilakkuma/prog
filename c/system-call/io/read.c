#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <unistd.h>

#define BUF_SIZE 10

int main(int argc, char **argv) {
    int fd;
    ssize_t cc;
    char buf[BUF_SIZE];

    if (argc != 2 ) {
        fprintf(stderr, "Require argument\n");
        exit(1);
    }

    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        perror("open");
        exit(1);
    }

    while ((cc = read(fd, buf, sizeof(buf))) > 0) {
        printf("%d bytes read\n", (int)cc);

        buf[(int)cc - 1] = '\0';

        printf("buf: %s\n", buf);
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
