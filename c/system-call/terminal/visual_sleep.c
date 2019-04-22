#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        fputs("Require 1 argument\n", stderr);
        exit(EXIT_FAILURE);
    }

    int i = 0;
    int n = strtol(argv[1], NULL, 10);

    char c[] = {'.', 'o', 'O'};

    for (i = 0; i < n; i++) {
        printf("%c\033[D", c[i % 3]);
        // printf("%c", c[i % 3]);
        fflush(stdout);
        sleep(1);
    }

    return 0;
}
