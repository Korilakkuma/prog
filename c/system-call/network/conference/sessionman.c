#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

#define MAX_ATTENDANTS 5
#define BUF_LEN 60

static char buf[BUF_LEN];
static fd_set mask;
static int width;
static int attendants;

typedef struct {
    int fd;
    char name[16];
} ATTENDANT;

static ATTENDANT p[MAX_ATTENDANTS];

static void send_all(int i, int n);
static void ending();

void enter(int i, int fd) {
    int len;
    static char *msg1 = "Type your name $ ";
    static char *msg2 = "Wait ...\n";

    p[i].fd = fd;

    memset(p[i].name, 0, 16);

    if (write(fd, msg1, strlen(msg1)) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }

    if ((len = read(fd, p[i].name, 16)) == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    // sprintf((p[i].name + (len - 1)), " --> ");
    strncat(p[i].name, " --> ", 22);

    if (write(fd, msg2, strlen(msg2)) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }
}

void sessionman_init(int num, int maxfd) {
    int i;
    static char *msg = "Communication Ready !\n";

    attendants = num;

    width = maxfd + 1;

    FD_ZERO(&mask);
    FD_SET(STDIN_FILENO, &mask);

    for (i = 0; i < num; i++) {
        FD_SET(p[i].fd, &mask);
    }

    for (i = 0; i < num; i++) {
        if (write(p[i].fd, msg, strlen(msg)) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }
    }
}

void sessionman_loop() {
    fd_set read0k;
    int i;

    while (1) {
        read0k = mask;

        if (select(width, (fd_set *)&read0k, NULL, NULL, NULL) < 0) {
            perror("select");
            exit(EXIT_FAILURE);
        }

        if (FD_ISSET(STDIN_FILENO, &read0k)) {
            ending();
        }

        for (i = 0; i < attendants; i++) {
            if (FD_ISSET(p[i].fd, &read0k)) {
                int n;

                if ((n = read(p[i].fd, buf, BUF_LEN)) == -1) {
                    perror("read");
                    exit(EXIT_FAILURE);
                }

                if (n > 0) {
                    send_all(i, n);
                }
            }
        }
    }
}

static void ending() {
    int i;

    for (i = 0; i < attendants; i++) {
        if (write(p[i].fd, "q", 1) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }
    }

    for (i = 0; i < attendants; i++) {
        if (close(p[i].fd) == -1) {
            perror("close");
            exit(EXIT_FAILURE);
        }
    }

    exit(EXIT_SUCCESS);
}

static void send_all(int i, int n) {
    int j;

    for (j = 0; j < attendants; j++) {
        if (write(p[j].fd, p[i].name, strlen(p[i].name)) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }

        if (write(p[j].fd, buf, n) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }
    }
}
