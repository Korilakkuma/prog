#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "bb.h"

#define DATA_DIR "./data"
#define MENU_STRING "1. call 2. canceled 3. circle 4. event 9 exit \n"

static int process(int soc, int item);

void service(int soc, char *myname) {
    pid_t mypid;
    char buf[BUF_LENGTH];
    int item;

    mypid = (int)getpid();

    snprintf(buf, BUF_LENGTH, "This is %s[%d] serving you.\n", myname, (int)mypid);

    if (write(soc, buf, strlen(buf)) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }

    do {
        if (write(soc, MENU_STRING, strlen(MENU_STRING)) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }

        if (read(soc, buf, 20) == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        sscanf(buf, "%d", &item);
    } while (process(soc, item));

    if (close(soc) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }
}

int process(int soc, int item) {
    int fd;
    int cnt;

    char filename[FILENAME_LENGTH];
    char buf[BUF_LENGTH];

    if (item == 9) {
        return 0;
    }

    snprintf(filename, FILENAME_LENGTH, "%s/data%d", DATA_DIR, item);

    if ((fd = open(filename, O_RDONLY)) == -1) {
        write(soc, "invalid number.\n", 17);
        return 1;
    }

    while ((cnt = read(fd, buf, BUF_LENGTH)) != 0) {
        if (write(soc, buf, cnt) == -1) {
            perror("write");
            return 1;
        }
    }

    if (close(fd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }

    return 1;
}

