#include <stdio.h>
#include <string.h>
#include "getcmd.h"

void getcmd(char *cmd, size_t size) {
    int len;
    char *p;

    fgets(cmd, size, stdin);

    len = strlen(cmd) + 1;

    if ((p = strchr(cmd, '\n')) == NULL) {
        cmd[len - 1] = '\0';
    } else {
        *p = '\0';
    }
}
