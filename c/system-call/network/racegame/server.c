#include <stdio.h>
#include <stdlib.h>
#include "race.h"
#include "sessionman.h"
#include "../lib/lib.h"

int main(int argc, char **argv) {
    int num;
    int final;
    int soc_waiting;
    int maxfd;

    if (argc != 3) {
        fputs("Usage: s players stages\n", stderr);
        exit(EXIT_FAILURE);
    }

    num = strtol(argv[1], NULL, 10);

    if ((num <= 0) || (num > MAX_PLAYERS)) {
        fprintf(stderr, "players limit = %d\n", MAX_PLAYERS);
        exit(EXIT_FAILURE);
    }

    final = strtol(argv[2], NULL, 10);

    if ((final <= 0) || (final > MAX_STAGES)) {
        fprintf(stderr, "stage limit = %d\n", MAX_STAGES);
        exit(EXIT_FAILURE);
    }

    if ((soc_waiting = mserver_socket(PORT, num)) == -1) {
        fputs("Cannot setup server\n", stderr);
        exit(EXIT_FAILURE);
    }

    maxfd = mserver_maccept(soc_waiting, num, enter);

    sessionman_init(num, final, maxfd);

    sessionman_loop();

    return 0;
}
