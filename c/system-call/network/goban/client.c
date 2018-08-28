#include "goban.h"

int main(void) {
    int soc;
    char my_stone = 'x';
    char peer_stone = 'o';
    char hostname[HOST_NAME_LENGTH];

    printf("Type hostname $ ");

    fgets(hostname, HOST_NAME_LENGTH, stdin);

    chop_newline(hostname, HOST_NAME_LENGTH);

    if ((soc = setup_client(hostname, PORT)) == -1) {
        exit(EXIT_FAILURE);
    }

    goban_init(soc, my_stone, peer_stone);

    while (1) {
        goban_show();

        printf("Go ahead > ");

        if (goban_my_turn() == -1) {
            break;
        }

        goban_show();

        printf("Wait ...\n");

        if (goban_peer_turn() == -1) {
            break;
        }
    }

    goban_destroy();
}
