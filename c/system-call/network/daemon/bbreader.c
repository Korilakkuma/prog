#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>

#include "../lib/lib.h"
#include "bb.h"

extern void session(int soc);

int main(void) {
    int soc = -1;

    char hostname[HOSTNAME_LENGTH];

    fputs("Type hostname % ", stderr);
    fgets(hostname, HOSTNAME_LENGTH, stdin);
    chop_newline(hostname, HOSTNAME_LENGTH);

    if ((soc = setup_client(hostname, PORT)) == -1) {
        exit(EXIT_FAILURE);
    }

    session(soc);

    return 0;
}
