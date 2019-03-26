#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include "mtalk2.h"

typedef struct {
    int flag;
    char name[MYNAME_LENGTH];
    struct sockaddr_in address;
} TALKER;

static int soc;
static char buf[BUF_LEN];
static TALKER talker[MAX_ATTENDANTS];

static struct sockaddr_in me;
static struct sockaddr_in from;
static socklen_t fromlen;
static int len;

static void do_login();
static void do_logout();
static int find_free_slot();
static void distribute();
static void ending();

int sessionman_init(in_port_t port) {
    int i;

    memset((char *)&me, 0, sizeof(me));

    me.sin_family = AF_INET;
    me.sin_addr.s_addr = htonl(INADDR_ANY);
    me.sin_port = htons(port);

    if ((soc = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("socket");
        return -1;
    }

    if (bind(soc, (struct sockaddr *)&me, sizeof(me)) == -1) {
        perror("bind");
        return -1;
    }

    fputs("Successfully bound !!\n", stderr);

    for (i = 0; i < MAX_ATTENDANTS; i++) {
        talker[i].flag = FREE;
    }

    signal(SIGINT, ending);

    return 0;
}

void sessionman_loop() {
    while (1) {
        fromlen = sizeof(from);

        if ((len = recvfrom(soc, buf, BUF_LEN, 0, (struct sockaddr *)&from, &fromlen)) == -1) {
            perror("recvfrom");
            exit(EXIT_FAILURE);
        }

        switch (buf[0]) {
            case LOGIN:
                do_login();
                break;
            case LOGOUT:
                do_logout();
                break;
            case DATA:
                distribute();
                break;
            default:
                break;
        }
    }
}

static void do_login() {
    int slot;

    if ((slot = find_free_slot()) == -1) {
        buf[0] = CANNOT_LOGIN;

        if (sendto(soc, buf, 2, 0, (struct sockaddr *)&from, (socklen_t)sizeof(from)) == -1) {
            perror("sendto");
            exit(EXIT_FAILURE);
        }

        return;
    }

    talker[slot].flag = IN_USE;

    strncpy(talker[slot].name, (buf + 1), MYNAME_LENGTH);

    talker[slot].address = from;

    printf("talker[%d]: %s logged in\n", slot, talker[slot].name);

    buf[0] = LOGIN_OK;

    snprintf((buf + 1), (sizeof(buf[0]) + sizeof(char)), "%02d\n", slot);

    if (sendto(soc, buf, 4, 0, (struct sockaddr *)&talker[slot].address, (socklen_t)sizeof(talker[slot].address)) == -1) {
        perror("sendto");
        exit(EXIT_FAILURE);
    }
}

static void do_logout() {
    int slot;

    sscanf((buf + 1), "%02d", &slot);

    talker[slot].flag = FREE;

    printf("talker[%d]: %s logged out\n", slot, talker[slot].name);
}

static int find_free_slot() {
    int slot;

    for (slot = 0; slot < MAX_ATTENDANTS; slot++) {
        if (talker[slot].flag == FREE) {
            return slot;
        }
    }

    return -1;
}

static void distribute() {
    int slot;

    for (slot = 0; slot < MAX_ATTENDANTS; slot++) {
        if (talker[slot].flag == FREE) {
            continue;
        }

        if (sendto(soc, buf, len, 0, (struct sockaddr *)&talker[slot].address, (socklen_t)sizeof(talker[slot].address)) == -1) {
            perror("sendto");
            exit(EXIT_FAILURE);
        }
    }
}

static void ending() {
    int slot;

    buf[0] = END;

    for (slot = 0; slot < MAX_ATTENDANTS; slot++) {
        if (talker[slot].flag == FREE) {
            continue;
        }

        if (sendto(soc, buf, 1, 0, (struct sockaddr *)&talker[slot].address, (socklen_t)sizeof(talker[slot].address)) == -1) {
            perror("perror");
            exit(EXIT_FAILURE);
        }
    }

    exit(EXIT_SUCCESS);
}
