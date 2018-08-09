#include <sys/types.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

#include <netdb.h>
#include <sys/uio.h>
#include <unistd.h>

char *httprequest = "GET / HTTP/1.0\r\n\r\n";

int main(int argc, char **argv) {
    struct addrinfo hints;
    struct addrinfo *addrs;

    int cc;
    int s;

    char buf[1024];

    if (argc != 3) {
        fputs("Require `http` or `https` and hostname\n", stderr);
        exit(EXIT_FAILURE);
    }

    memset(&hints, 0, sizeof(hints));

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((cc = getaddrinfo(argv[2], argv[1], &hints, &addrs)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(cc));
        exit(EXIT_FAILURE);
    }

    if ((s = socket(addrs->ai_family, addrs->ai_socktype, addrs->ai_protocol)) == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    if (connect(s, addrs->ai_addr, addrs->ai_addrlen) == -1) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(addrs);

    if (write(s, httprequest, strlen(httprequest)) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }

    while ((cc = read(s, buf, sizeof(buf))) > 0) {
        if (write(STDOUT_FILENO, buf, cc) == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }
    }

    if (shutdown(s, SHUT_RDWR) == -1) {
        perror("shutdown");
        exit(EXIT_FAILURE);
    }

    if (close(s) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }

    return 0;
}
