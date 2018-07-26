#include <errno.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>

int main(int argc, char **argv) {
    struct stat sb;
    DIR *dp;
    struct dirent *dep;
    int i;
    int ndir     = 0;
    int nreg     = 0;
    int nchr     = 0;
    int nblk     = 0;
    int nfifo    = 0;
    int nsock    = 0;
    int nlnk     = 0;
    int nunknown = 0;

    if (argc != 2) {
        fputs("Require 1 argument\n", stderr);
        exit(EXIT_FAILURE);
    }

    printf("%s: ", argv[1]);

    if (chdir(argv[1]) == -1) {
        perror("chdir");
        exit(EXIT_FAILURE);
    }

    if ((dp = opendir(".")) == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    errno = 0;

    while ((dep = readdir(dp)) != NULL) {
        if (lstat(dep->d_name, &sb) == -1) {
            continue;
        }

        switch (sb.st_mode & S_IFMT) {
            case S_IFDIR:
                ndir++;
                break;
            case S_IFREG:
                nreg++;
                break;
            case S_IFCHR:
                nchr++;
                break;
            case S_IFBLK:
                nblk++;
                break;
            case S_IFIFO:
                nfifo++;
                break;
            case S_IFSOCK:
                nsock++;
                break;
            case S_IFLNK:
                nlnk++;
                break;
            default:
                nunknown++;
                break;
        }
    }

    ndir -= 2;

    for (i = 0; i < ndir; i++) {
        putchar('/');
    }

    for (i = 0; i < nreg; i++) {
        putchar('-');
    }

    for (i = 0; i < nchr; i++) {
        putchar('%');
    }

    for (i = 0; i < nblk; i++) {
        putchar('#');
    }

    for (i = 0; i < nfifo; i++) {
        putchar('|');
    }

    for (i = 0; i < nsock; i++) {
        putchar('=');
    }

    for (i = 0; i < nlnk; i++) {
        putchar('@');
    }

    for (i = 0; i < nunknown; i++) {
        putchar('?');
    }

    putchar('\n');

    closedir(dp);

    return 0;
}
