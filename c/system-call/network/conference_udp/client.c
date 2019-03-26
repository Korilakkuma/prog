#include <stdio.h>
#include <stdlib.h>
#include "mtalk2.h"
#include "session.h"
#include "../lib/lib.h"

int main(void) {
    char hostname[HOSTNAME_LENGTH];

    fputs("Type hostname $ ", stderr);
    fgets(hostname, HOSTNAME_LENGTH, stdin);
    chop_newline(hostname, HOSTNAME_LENGTH);

    if (session_setupclient(hostname, PORT) < 0) {
        exit(EXIT_FAILURE);
    }

    session_init();

    session_loop();

    return 0;
}
