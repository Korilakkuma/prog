#include "lib.h"

enum {
    QUEUE_SIZE = 5
};

int setup_server(in_port_t port) {
    struct sockaddr_in ca;

    socklen_t ca_len = sizeof(ca);

    struct addrinfo hints;
    struct addrinfo *res;

    int s;
    int ws;

    char portstring[8];
    char hostname[HOSTNAME_LENGTH];

    if (gethostname(hostname, HOSTNAME_LENGTH) == -1) {
        perror("gethostname");
        return -1;
    }

    snprintf(portstring, 8, "%d", port);

    memset(&hints, 0, sizeof(struct addrinfo));

    hints.ai_family   = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(hostname, portstring, &hints, &res) != 0) {
        perror("getaddrinfo");
        return -1;
    }

    if ((s = socket(res->ai_family, res->ai_socktype, res->ai_protocol)) == -1) {
        perror("socket");
        return -1;
    }

    if (bind(s, res->ai_addr, res->ai_addrlen) == -1) {
        perror("bind");
        return -1;
    }

    if (listen(s, QUEUE_SIZE)) {
        perror("listen");
        return -1;
    }

    fputs("Successfully bound !! Now waiting ...\n", stderr);

    if ((ws = accept(s, (struct sockaddr *)&ca, &ca_len)) == -1) {
        perror("accept");
        return -1;
    }

    if (close(s) == -1) {
        perror("close");
        return -1;
    }

    freeaddrinfo(res);

    return ws;
}
