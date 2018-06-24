#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
    MY_NAME_LEN = 15
};

char *name;

int myname;
int notmyname;
int junkchars;

void processword(void);

int main(int argc, char **argv) {
    int c;

    if (argc != 2) {
        fprintf(stderr, "Require 1 argument\n");
        exit(1);
    }

    name = argv[1];

    assert(strlen(name) <= MY_NAME_LEN);

    while ((c = getchar()) != EOF) {
        if (isalpha(c)) {
            if (ungetc(c, stdin) == EOF) {
                fputs("cannot `ungetc`\n", stderr);
                exit(1);
            } else {
                processword();
            }
        } else {
            junkchars++;
        }
    }

    printf("my name %d, not my name %d, junk chars %d\n", myname, notmyname, junkchars);

    return 0;
}

void processword(void) {
    int c;
    int i = 0;
    char buf[MY_NAME_LEN + 2];

    while ((c = getchar()) != EOF) {
        if (isalpha(c)) {
            buf[i++] = c;

            if (i == (sizeof(buf) - 1)) {
                while ((c = getchar()) != EOF) {
                    if (isalpha(c)) {
                        continue;
                    }

                    if (ungetc(c, stdin) == EOF) {
                        fputs("cannot `ungetc`\n", stderr);
                        exit(1);
                    }

                    break;
                }

                goto wordgot;
            }
        } else {
            if (ungetc(c, stdin) == EOF) {
                fputs("cannot `ungetc`\n", stderr);
                exit(1);
            }

            goto wordgot;
        }
    }

wordgot:
    buf[i] = '\0';

    printf("%s\n", buf);

    if (strcmp(buf, name)) {
        notmyname++;
    } else {
        myname++;
    }
}
