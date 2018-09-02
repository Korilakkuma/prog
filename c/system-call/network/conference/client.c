#include "session.h"
#include "../lib/lib.h"

int main(void) {
    int soc;
    char hostname[HOSTNAME_LENGTH];

    fputs("Type hostname $ ", stderr);
    fgets(hostname, HOSTNAME_LENGTH, stdin);
    chop_newline(hostname, HOSTNAME_LENGTH);

    if ((soc = setup_client(hostname, PORT)) == -1) {
        exit(EXIT_FAILURE);
    }

    session_init(soc);

    session_loop();

    return 0;
}
