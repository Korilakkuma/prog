/**
 * 1. echo "experiment 8000/tcp" >> /etc/services
 * 2. echo "experiment stream tcp nowait root (path) bb9d" >> /etc/inetd.conf
 *
 * or
 *
 * 2. touch /etc/xinetd.d/experiment
 *
 *    service experiment
 *    {
 *        id          = experiment
 *        socket_type = stream
 *        protocol    = tcp
 *        user        = root
 *        wait        = no
 *        disable     = no
 *        server      = (path)/bb9d
 *    }
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

#include "bb.h"

#define SOC 0

extern void service(int soc, char * myname);

int main(int argc, char **argv) {
    if (argc != 2) {
        fputs("Require 1 argument\n", stderr);
        exit(EXIT_FAILURE);
    }

    openlog(argv[0], LOG_PID, LOG_USER);
    syslog(LOG_ERR, "startup experiment");

    service(SOC, argv[0]);

    syslog(LOG_ERR, "shotdown experiment");
    closelog();

    if (shutdown(SOC, 2) == -1) {
        exit(EXIT_FAILURE);
    }

    return 0;
}
