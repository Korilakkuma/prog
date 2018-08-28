#include "goban.h"

#define GOBAN_SIZE 5
#define ROW_LENGTH 6
#define DATA_SIZE 10

static char goban_my_stone;
static char goban_peer_stone;

static char goban_plane[][ROW_LENGTH] = { "+123+", "a...|", "b...|", "c...|", "+---+" };

static int goban_soc;

void goban_init(int soc, char my_stone, char peer_stone) {
    goban_soc = soc;
    goban_my_stone = my_stone;
    goban_peer_stone = peer_stone;
}

void goban_show() {
    int i;

    for (i = 0; i < GOBAN_SIZE; i++) {
        printf("%s\n", goban_plane[i]);
    }
}

int goban_peer_turn() {
    char data[DATA_SIZE];
    int x, y;

    if (read(goban_soc, data, DATA_SIZE) == -1) {
        perror("read");
        return -1;
    }

    if (data[0] == 'q') {
        return -1;
    }

    y = (int)data[0] - (int)'a' + 1;
    x = (int)data[1] - (int)'0';

    goban_plane[y][x] = goban_peer_stone;

    return 1;
}

int goban_my_turn() {
    char data[DATA_SIZE];
    int x, y;

    while (1) {
        fgets(data, DATA_SIZE, stdin);

        if (data[0] == 'q') {
            write(goban_soc, data, 1);
            return -1;
        }

        if ((data[0] < 'a') || (data[0] > 'c') || (data[1] < '1') || (data[1] > '3')) {
            continue;
        }

        break;
    }

    y = (int)data[0] - (int)'a' + 1;
    x = (int)data[1] - (int)'0';

    goban_plane[y][x] = goban_my_stone;

    if (write(goban_soc, data, DATA_SIZE) == -1) {
        perror("write");
        return -1;
    }

    return 1;
}

void goban_destroy() {
    if (shutdown(goban_soc, SHUT_RDWR) == -1) {
        perror("shutdown");
        exit(EXIT_FAILURE);
    }

    if (close(goban_soc) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }
}
