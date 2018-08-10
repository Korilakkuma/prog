#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static void loop(void) {
    int i;

    for (i = 0; i < 0xFFFFFF; i++) ;
}

int main(int argc, char **argv) {
    unsigned int second;

    if (argc != 2) {
        fputs("Require 1 argument\n", stderr);
        exit(EXIT_FAILURE);
    }

    second = (unsigned int)strtol(argv[1], NULL, 10);

    alarm(second);

    while (1) {
        loop();
        putc('.', stdout);
        fflush(stdout);
    }

    return 0;
}
