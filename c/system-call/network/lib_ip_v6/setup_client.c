#include "lib.h"

int setup_client(char *hostname, in_port_t port) {
    struct addrinfo hints;
    struct addrinfo *res;

    int s;

    char portstring[8];

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

    if (connect(s, (struct sockaddr *)res->ai_addr, res->ai_addrlen) == -1) {
        perror("connect");
        return -1;
    }

    fputs("Connected !!\n", stderr);

    freeaddrinfo(res);

    return s;
}
