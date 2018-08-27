#include "lib.h"

enum {
    QUEUE_SIZE = 5
};

int setup_server(in_port_t port) {
    int s;
    int ws;
    int soval;

    struct sockaddr_in sa;
    struct sockaddr_in ca;

    socklen_t ca_len;

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        return -1;
    }

    soval = 1;

    if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &soval, sizeof(soval)) == -1) {
        perror("setsockopt");
        return -1;
    }

    memset(&sa, 0, sizeof(sa));

    sa.sin_len = sizeof(sa);
    sa.sin_family = AF_INET;
    sa.sin_port = htons(port);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(s, (struct sockaddr *)&sa, sizeof(sa)) == -1) {
        perror("bind");
        return -1;
    }

    if (listen(s, QUEUE_SIZE)) {
        perror("listen");
        return -1;
    }

    ca_len = sizeof(ca);

    if ((ws = accept(s, (struct sockaddr *)&ca, &ca_len)) == -1) {
        perror("accept");
        return -1;
    }

    fputs("Connected !!\n", stderr);

    return ws;
}
