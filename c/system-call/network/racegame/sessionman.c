#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "race.h"

#define MAX_DAMAGE 10
#define NAME_LENGTH 16

static int soc[MAX_PLAYERS];
static char name[MAX_PLAYERS][NAME_LENGTH];
static char p[MAX_PLAYERS * PLAYER_SIZE];

static fd_set mask;
static fd_set read0k;
static int width;

static int final;
static int num;
static int reached;
static int crashed;

static char g[MAX_PLAYERS * GRADE_SIZE];

static void recv_data();
static void send_data();
static void ending();

void enter(int i, int fd) {
    int len;
    static char *login_msg = "Type your name $ ";
    char msg[32];

    soc[i] = fd;

    if (write(soc[i], login_msg, (strlen(login_msg) + 1)) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }

    if (read(soc[i], name[i], NAME_LENGTH) == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    snprintf(msg, 32, "%d\n", i);

    if (write(soc[i], msg, (strlen(msg) + 1)) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }

    printf("[%d] %s\n", i, name[i]);
}

void sessionman_init(int n, int fin, int maxfd) {
    int i;
    static char msg[10];

    num = n;
    final = fin;

    width = maxfd + 1;

    FD_ZERO(&mask);
    FD_SET(STDIN_FILENO, &mask);

    for (i = 0; i < num; i++) {
        FD_SET(soc[i], &mask);
    }

    snprintf(msg, 10, "%d %d", num, final);

    for (i = 0; i < num; i++) {
        if (write(soc[i], msg, 10) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }
    }

    reached = 0;
    crashed = 0;
}

void sessionman_loop() {
    while ((reached + crashed) < num) {
        recv_data();
        send_data();
    }

    ending();
}

static void recv_data() {
    int i;

    read0k = mask;

    if (select(width, &read0k, NULL, NULL, NULL) < 0) {
        perror("select");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < num; i++) {
        if (FD_ISSET(soc[i], (fd_set *)&read0k)) {
            int n;

            if ((n = read(soc[i], &p[i * PLAYER_SIZE], PLAYER_SIZE)) == -1) {
                perror("read");
                exit(EXIT_FAILURE);
            }

            if (p[(i * PLAYER_SIZE) + DAMAGE] >= MAX_DAMAGE) {
                g[((num - crashed - 1) * GRADE_SIZE) + ENTRYNUM] = i;
                strncpy(&g[((num - crashed - 1) * GRADE_SIZE) + ENTRYNAME], name[i], NAME_LENGTH);
                crashed++;
            }

            if (p[(i * PLAYER_SIZE) + STAGE] > final) {
                g[(reached * GRADE_SIZE) + ENTRYNUM] = (char)i;
                strncpy(&g[(reached * GRADE_SIZE) + ENTRYNAME], name[i], NAME_LENGTH);
                reached++;
            }
        }
    }
}

static void send_data() {
    int i;

    for (i = 0; i < num; i++) {
        if (FD_ISSET(soc[i], &read0k)) {
            if (write(soc[i], p, (PLAYER_SIZE * num)) == -1) {
                perror("write");
                exit(EXIT_FAILURE);
            }
        }
    }
}

static void ending() {
    int i;

    for (i = 0; i < num; i++) {
        if (write(soc[i], g, (GRADE_SIZE * num)) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }
    }
}
