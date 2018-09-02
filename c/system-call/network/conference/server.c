#include "sessionman.h"
#include "../lib/lib.h"

int main(int argc, char **argv) {
    int num;
    int soc;
    int maxfd;

    if (argc != 2) {
        fputs("Usage: s attendants\n", stderr);
        exit(EXIT_FAILURE);
    }

    num = (int)strtol(argv[1], NULL, 10);

    if ((num <= 0) || (num > MAX_ATTENDANTS)) {
        fprintf(stderr, "Attendants limit = %d\n", MAX_ATTENDANTS);
        exit(EXIT_FAILURE);
    }

    if ((soc = mserver_socket(PORT, num)) == -1) {
        fputs("Cannot setup server\n", stderr);
        exit(EXIT_FAILURE);
    }

    maxfd = mserver_maccept(soc, num, enter);

    sessionman_init(num, maxfd);

    sessionman_loop();

    return 0;
}
