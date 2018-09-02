#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>

#define PORT (in_port_t)8000
#define HOSTNAME_LENGTH 64

extern void session_init(int soc);
extern void session_loop();
