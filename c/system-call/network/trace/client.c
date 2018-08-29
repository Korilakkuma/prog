#include "session.h"
#include "tag.h"

int main(void) {
    int soc;
    char hostname[HOSTNAME_LENGTH];

    printf("Type hostname $ ");

    fgets(hostname, HOSTNAME_LENGTH, stdin);

    chop_newline(hostname, HOSTNAME_LENGTH);

    if ((soc = setup_client(hostname, PORT)) == -1) {
        exit(EXIT_FAILURE);
    }

    session_init(soc, 'x', 10, 10, 'o', 1, 1);

    session_loop();

    return 0;
}
