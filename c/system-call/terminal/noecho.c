#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int main(void) {
    int c;

    struct termios new, old;

    tcgetattr(STDIN_FILENO, &old);

    new = old;

    new.c_lflag &= ~ECHO;

    tcsetattr(STDIN_FILENO, TCSANOW, &new);

    while ((c = fgetc(stdin)) != EOF) {
        fputc(c, stdout);
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &old);

    return 0;
}
