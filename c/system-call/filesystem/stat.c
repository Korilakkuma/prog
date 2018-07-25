#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv) {
    struct stat *sb;

    if (argc != 2) {
        fputs("Require 1 argument\n", stderr);
        exit(EXIT_FAILURE);
    }

    if ((sb = (struct stat *)malloc(sizeof(stat))) == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    if (stat(argv[1], sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    printf("Information for %s:\n", argv[1]);
    printf("  st_ino   = %d\n", (int)sb->st_ino);
    printf("  st_mode  = %d\n", (int)sb->st_mode);
    printf("  st_nlink = %d\n", (int)sb->st_nlink);
    printf("  st_uid   = %d\n", (int)sb->st_uid);
    printf("  st_gid   = %d\n", (int)sb->st_gid);
    printf("  st_size  = %d\n", (int)sb->st_size);

    free(sb);

    return 0;
}
