#include "lib.h"

int setup_client(char *hostname, in_port_t port) {
    struct hostent *server_ent;
    struct sockaddr_in server;

    int s;

    if ((server_ent = gethostbyname(hostname)) == NULL) {
        perror("gethostbyname");
        return -1;
    }

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        return -1;
    }

    memset((char *)&server, 0, sizeof(server));

    server.sin_len = sizeof(server);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    memcpy((char *)&server.sin_addr, server_ent->h_addr, server_ent->h_length);
    // memmove(&server.sin_addr, server_ent->h_addr_list[0], sizeof(server.sin_addr));

    if (connect(s, (struct sockaddr *)&server, sizeof(server)) == -1) {
        perror("connect");
        return -1;
    }

    fputs("Connected !!\n", stderr);

    return s;
}
