#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

enum {
    PERM_LEN = 9
};

int main(int argc, char **argv) {
    struct stat *sbuf;
    int i;
    char perm[PERM_LEN + 1];

    if (argc != 2) {
        fputs("Require 1 argument\n", stderr);
        exit(EXIT_FAILURE);
    }

    if ((sbuf = (struct stat *)malloc(sizeof(stat))) == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    if (stat(argv[1], sbuf) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    for (i = 0; i < PERM_LEN; i++) {
        perm[i] = '-';
    }

    perm[PERM_LEN] = '\0';

    if (sbuf->st_mode & S_IRUSR) { perm[0] = 'r'; }
    if (sbuf->st_mode & S_IWUSR) { perm[1] = 'w'; }
    if (sbuf->st_mode & S_IXUSR) { perm[2] = 'x'; }
    if (sbuf->st_mode & S_ISUID) { perm[2] = 's'; }
    if (sbuf->st_mode & S_IRGRP) { perm[3] = 'r'; }
    if (sbuf->st_mode & S_IWGRP) { perm[4] = 'w'; }
    if (sbuf->st_mode & S_IXGRP) { perm[5] = 'x'; }
    if (sbuf->st_mode & S_ISGID) { perm[5] = 's'; }
    if (sbuf->st_mode & S_IROTH) { perm[6] = 'r'; }
    if (sbuf->st_mode & S_IWOTH) { perm[7] = 'w'; }
    if (sbuf->st_mode & S_IXOTH) { perm[8] = 'x'; }
    if (sbuf->st_mode & S_ISVTX) { perm[8] = 't'; }

    puts(perm);

    return 0;
}
