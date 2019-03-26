#include <stdio.h>
#include <stdlib.h>
#include "mtalk2.h"
#include "sessionman.h"

int main(void) {
    if (sessionman_init(PORT) == -1) {
        fputs("Cannot setup server\n", stderr);
        exit(EXIT_FAILURE);
    }

    sessionman_loop();

    return 0;
}
