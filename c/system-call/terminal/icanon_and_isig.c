#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

int main(void) {
    int c;

    struct termios new, old;

    tcgetattr(STDIN_FILENO, &old);

    new = old;

    new.c_lflag &= ~(ICANON | ISIG);
    new.c_cc[VMIN]  = 1;
    new.c_cc[VTIME] = 0;

    tcsetattr(STDIN_FILENO, TCSANOW, &new);

    while ((c = fgetc(stdin)) != EOF) {
        if (c == 'q') {
            exit(EXIT_SUCCESS);
        }

        fputc(c, stdout);
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &old);

    return 0;
}
