#include <sys/types.h>
#include "../lib/lib.h"

#define PORT (in_port_t)8000
#define HOST_NAME_LENGTH 64

extern void goban_init(int soc, char my_stone, char peer_stone);
extern void goban_show();
extern void goban_destroy();
extern int goban_peer_turn();
extern int goban_my_turn();
