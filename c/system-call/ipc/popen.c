#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    FILE *fp;
    char buf[1024];

    if (argc != 2) {
        fputs("Require 1 argument\n", stderr);
        exit(EXIT_FAILURE);
    }

    if ((fp = popen(argv[1], "r")) == NULL) {
        perror("popen");
        exit(EXIT_FAILURE);
    }

    fgets(buf, sizeof(buf), fp);

    printf("%s", buf);

    pclose(fp);

    return 0;
}
