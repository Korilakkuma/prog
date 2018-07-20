#include <errno.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int main(int argc, char **argv) {
    DIR *dirp;
    struct dirent *p;

    if (argc != 2) {
        fputs("Require 1 argument\n", stderr);
        exit(EXIT_FAILURE);
    }

    if ((dirp = opendir(argv[1])) == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    errno = 0;

    while ((p = readdir(dirp)) != NULL) {
        printf("%llu %s\n", p->d_fileno, p->d_name);
    }

    if (errno != 0) {
        perror("readdir");
        exit(EXIT_FAILURE);
    }

    if (closedir(dirp) != 0) {
        perror("closedir");
        exit(EXIT_FAILURE);
    }

    return 0;
}
