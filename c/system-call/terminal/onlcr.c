#include <stdio.h>
#include <termios.h>
#include <unistd.h>

int main(void) {
    int c;
    struct termios new, old;

    tcgetattr(STDIN_FILENO, &old);

    new = old;

    new.c_oflag &= ~ONLCR;

    tcsetattr(STDIN_FILENO, TCSANOW, &new);

    while ((c = getchar()) != EOF) {
        putchar(c);
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &old);

    return 0;
}
