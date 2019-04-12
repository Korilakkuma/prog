#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "../lib/lib.h"
#include "bb.h"

#define SERV_NAME "experiment"
#define SERV_PROTPO "tcp"

extern void session(int soc);

static int setup(char *hostname) {
    int soc;

    struct servent *server_info;
    struct hostent *host_info;
    struct sockaddr_in server;

    if ((server_info = getservbyname(SERV_NAME, SERV_PROTPO)) == NULL) {
        perror("getservbyname");
        return -1;
    }

    if ((host_info = gethostbyname(hostname)) == NULL) {
        perror("gethostbyname");
        return -1;
    }

    memset((char *)&server, 0, sizeof(server));

    server.sin_family = AF_INET;
    server.sin_port = server_info->s_port;

    memcpy((char *)&server.sin_addr, host_info->h_addr, host_info->h_length);

    if ((soc = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        return -1;
    }

    if (connect(soc, (struct sockaddr *)&server, sizeof(server)) == -1) {
        perror("connect");
        return -1;
    }

    fputs("connected\n", stderr);

    return soc;
}

int main(void) {
    int soc = -1;
    char hostname[HOSTNAME_LENGTH];

    fputs("Type hosname % ", stderr);
    fgets(hostname, HOSTNAME_LENGTH, stdin);
    chop_newline(hostname, HOSTNAME_LENGTH);

    if ((soc = setup(hostname)) == -1) {
        exit(EXIT_FAILURE);
    }

    session(soc);

    return 0;
}
