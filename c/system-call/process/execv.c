#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Require argument at least\n");
        exit(EXIT_FAILURE);
    }

    char *args[3];
    char buf[PATH_MAX];
    char *s;
    char *p;
    int len;

    fgets(buf, sizeof(buf), stdin);

    len = strlen(buf) + 1;

    s = (char *)malloc(len);

    strncpy(s, buf, len);

    if ((p = strchr(s, '\n')) == NULL) {
        s[len - 1] = '\0';
    } else {
        *p = '\0';
    }

    args[0] = argv[2];
    args[1] = s;
    args[2] = NULL;

    fflush(stdout);

    execv(argv[1], args);

    perror("execv");

    exit(EXIT_FAILURE);
}
