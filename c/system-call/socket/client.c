#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/uio.h>
#include <unistd.h>

#define SERVER_ADDR "127.0.0.1"
#define SERVER_PORT 8080

int main(void) {
    int s;
    int cc;

    struct sockaddr_in sa;

    char buf[1024];

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&sa, 0, sizeof(sa));

    sa.sin_len = sizeof(sa);
    sa.sin_family = AF_INET;
    sa.sin_port = htons(SERVER_PORT);
    sa.sin_addr.s_addr = inet_addr(SERVER_ADDR);

    fprintf(stderr, "Connecting to the server ...\n");

    if (connect(s, (struct sockaddr *)&sa, sizeof(sa)) == -1) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    fprintf(stderr, "Connected.\n");

    fprintf(stderr, "Message from the server:\n\n");

    while ((cc = read(s, buf, sizeof(buf))) > 0) {
        write(STDOUT_FILENO, buf, cc);
    }

    if (cc == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    fprintf(stderr, "\n\nEnd receving.\n");

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
