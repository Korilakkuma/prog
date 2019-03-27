#include "lib.h"

int mserver_socket(in_port_t port, int backlog) {
    struct addrinfo hints;
    struct addrinfo *res;

    int ws;

    char portstring[8];
    char hostname[HOSTNAME_LENGTH];

    snprintf(portstring, 8, "%d", port);

    memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(hostname, portstring, &hints, &res) != 0) {
        perror("getaddrinfo");
        return -1;
    }

    if ((ws = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1) {
        perror("socket");
        return -1;
    }

    if (bind(ws, res->ai_addr, res->ai_addrlen) == -1) {
        perror("bind");
        return -1;
    }

    if (listen(ws, backlog)) {
        perror("listen");
        return -1;
    }

    fputs("Now waiting ...\n", stderr);

    freeaddrinfo(res);

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
        return -1;
    }

    return fd;
}
