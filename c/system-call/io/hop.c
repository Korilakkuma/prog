#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <unistd.h>

#define COUNT 8

int main(void) {
    int fd;
    int i;

    if ((fd = open("hop.out", (O_WRONLY | O_CREAT | O_TRUNC), 0666)) == -1) {
        perror("open");
        exit(1);
    }

    for (i = 0; i < COUNT; i++) {
        if (write(fd, "hop", 3) == -1) {
            perror("write");
            exit(1);
        }

        if (lseek(fd, 3, SEEK_CUR) == -1) {
            perror("lseek");
            exit(1);
        }
    }

    if (close(fd) == -1) {
        perror("close");
        exit(1);
    }

    return 0;
}
