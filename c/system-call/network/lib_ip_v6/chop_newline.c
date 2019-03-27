#include "lib.h"

char *chop_newline(char *str, size_t len) {
    size_t n = strlen(str);

    if ((n < len) && (str[n - 1] == '\n')) {
        str[n - 1] = '\0';
    }

    return str;
}
