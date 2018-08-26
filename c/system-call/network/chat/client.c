#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/uio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netdb.h>

#define SERVER_PORT (in_port_t)8080

char buf[1024];

static void sendmessage(int s) {
    if (fgets(buf, sizeof(buf), stdin) == NULL) {
        perror("fgets");
        exit(EXIT_SUCCESS);
    }

    if (write(s, buf, strlen(buf)) == -1) {
        fprintf(stderr, "send error\n");
        return;
    }

    clearerr(stdin);
}

static void receivemessage(int s) {
    int cc;

    if ((cc = read(s, buf, sizeof(buf))) == -1) {
        fprintf(stderr, "receive error\n");
        return;
    }

    write(STDOUT_FILENO, buf, cc);
}

int main(void) {
    int s;

    struct hostent *server_ent;
    struct sockaddr_in sa;

    char *hostname = "localhost";

    if ((server_ent = gethostbyname(hostname)) == NULL) {
        perror("gethostbyname");
        exit(EXIT_FAILURE);
    }

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    memset(&sa, 0, sizeof(sa));

    sa.sin_len = sizeof(sa);
    sa.sin_family = AF_INET;
    sa.sin_port = htons(SERVER_PORT);

    memcpy((char *)&sa.sin_addr, server_ent->h_addr, server_ent->h_length);

    fprintf(stderr, "Connecting to the server ...\n");

    if (connect(s, (struct sockaddr *)&sa, sizeof(sa)) == -1) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    fprintf(stderr, "Connected.\n");

    while (1) {
        fprintf(stderr, "[Server -> Client] ");

        receivemessage(s);

        fprintf(stderr, "Message received.\n");

        fprintf(stderr, "[Client -> Server] $ ");

        sendmessage(s);

        fprintf(stderr, "Message sent.\n");
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
