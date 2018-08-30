#include "lib.h"

int mserver_socket(in_port_t port, int backlog) {
    int ws;
    int soval;

    struct sockaddr_in sa;

    if ((ws = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        return -1;
    }

    soval = 1;

    if (setsockopt(ws, SOL_SOCKET, SO_REUSEADDR, &soval, sizeof(soval)) == -1) {
        perror("setsockopt");
        return -1;
    }

    memset(&sa, 0, sizeof(sa));

    sa.sin_len = sizeof(sa);
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(ws, (struct sockaddr *)&sa, sizeof(sa)) == -1) {
        perror("bind");
        return -1;
    }

    if (listen(ws, backlog)) {
        perror("listen");
        return -1;
    }

    fputs("Now waiting ...\n", stderr);

    return ws;
}

int mserver_maccept(int ws, int limit, void (*callback)()) {
    int i;
    int fd;

    struct sockaddr_in ca;

    socklen_t ca_len = sizeof(ca);

    for (i = 0; i < limit; i++) {
        if ((fd = accept(ws, (struct sockaddr *)&ca, &ca_len)) == -1) {
            perror("accept");
            return -1;
        }

        (*callback)(i, fd);
    }

    if (close(ws) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }

    return fd;
}
