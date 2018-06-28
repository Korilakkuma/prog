#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    char *env_value;

    if (argc != 2) {
        fprintf(stderr, "Require 1 argument\n");
        exit(0);
    }

    if ((env_value = getenv(argv[1])) != NULL) {
        printf("%s = %s\n", argv[1], env_value);
    } else {
        printf("%s is not set\n", argv[1]);
    }

    return 0;
}
