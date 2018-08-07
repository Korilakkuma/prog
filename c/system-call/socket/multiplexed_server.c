#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <unistd.h>

enum {
    SERVER_PORT = 8080,
    QUEUE_SIZE  = 5,
    MAX_CLIENTS = 10
};

int clients[MAX_CLIENTS];
int nclients = 0;

static void sorry(int ws) {
    char *message = "Sorry, it's full.\n";

    write(ws, message, strlen(message));
}

static void delete_client(int ws) {
    int i;

    for (i = 0; i < nclients; i++) {
        if (clients[i] == ws) {
            clients[i] = clients[nclients - 1];
            nclients--;
            break;
        }
    }
}

static void talk(int ws) {
    int i;
    int cc;
    char c;

    do {
        if ((cc = read(ws, &c, 1)) == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        } else if (cc == 0) {
            shutdown(ws, SHUT_RDWR);
            close(ws);
            delete_client(ws);
            fprintf(stderr, "Connection closed on descriptor %d.\n", ws);
            return;
        }

        for (i = 0; i < nclients; i++) {
            write(clients[i], &c, 1);
        }
    } while (c != '\n');
}

int main(void) {
    int s;
    int soval;
    struct sockaddr_in sa;

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    soval = 1;

    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &soval, sizeof(soval)) == -1) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    memset(&sa, 0, sizeof(sa));

    sa.sin_len = sizeof(sa);
    sa.sin_family = AF_INET;
    sa.sin_port = htons(SERVER_PORT);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(s, (struct sockaddr *)&sa, sizeof(sa)) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    if (listen(s, QUEUE_SIZE)) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    fprintf(stderr, "Ready.\n");

    while (1) {
        int i;
        int maxfd;
        fd_set readfds;

        FD_ZERO(&readfds);
        FD_SET(s, &readfds);

        maxfd = s;

        for (i = 0; i < nclients; i++) {
            FD_SET(clients[i], &readfds);

            if (clients[i] > maxfd) {
                maxfd = clients[i];
            }
        }

        if (select((maxfd + 1), &readfds, NULL, NULL, NULL) < 0) {
            perror("select");
            exit(EXIT_FAILURE);
        }

        if (FD_ISSET(s, &readfds)) {
            int ws;
            struct sockaddr_in ca;
            socklen_t ca_len;

            ca_len = sizeof(ca);

            if ((ws = accept(s, (struct sockaddr *)&ca, &ca_len)) == -1) {
                perror("accept");
                continue;
            }

            if (nclients >= MAX_CLIENTS) {
                sorry(ws);
                shutdown(ws, SHUT_RDWR);
                close(ws);
                fprintf(stderr, "Refusd a new continue.\n");
            } else {
                clients[nclients] = ws;
                nclients++;
                fprintf(stderr, "Accepted a connection on descriptor %d.\n", ws);
            }
        }

        for (i = 0; i < nclients; i++) {
            if (FD_ISSET(clients[i], &readfds)) {
                talk(clients[i]);
                break;
            }
        }
    }
}
