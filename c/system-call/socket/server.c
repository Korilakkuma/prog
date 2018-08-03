#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/uio.h>
#include <unistd.h>

#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 8080

enum {
    QUEUE_SIZE = 5
};

char *message = "Hello !\nGood bye !!\n";

int main(void) {
    int s;
    int ws;
    int soval;
    int cc;

    struct sockaddr_in sa;
    struct sockaddr_in ca;

    socklen_t ca_len;

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
        fprintf(stderr, "Waiting for a connection ... \n");

        ca_len = sizeof(ca);

        if ((ws = accept(s, (struct sockaddr *)&ca, &ca_len)) == -1) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        fprintf(stderr, "Connection established ... \n");

        fprintf(stderr, "Sending the message ... \n");

        if ((cc = write(ws, message, strlen(message))) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }

        fprintf(stderr, "Message sent.\n");

        if (shutdown(ws, SHUT_RDWR) == -1) {
            perror("shutdown");
            exit(EXIT_FAILURE);
        }

        if (close(ws) == -1) {
            perror("close");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}
