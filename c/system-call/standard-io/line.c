#include <stdio.h>

#define LINE_LEN 1024

int main(void) {
    char buf[LINE_LEN];

    while (fgets(buf, sizeof(buf), stdin) != NULL) {
        if (fputs(buf, stdout) == EOF) {
            perror("fputs");
        }
    }

    return 0;
}
