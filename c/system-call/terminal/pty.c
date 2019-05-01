#define _XOPEN_SOURCE 600

#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/uio.h>
#include <termios.h>
#include <unistd.h>

int open_master(void) {
    int fd = posix_openpt(O_RDWR);

    grantpt(fd);
    unlockpt(fd);

    return fd;
}

int open_slave(int fd_master) {
    int fd_slave;

    if ((fd_slave = open(ptsname(fd_master), O_RDWR)) == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    return fd_slave;
}

struct termios set_tty_raw(int fd) {
    struct termios old, new;

    tcgetattr(fd, &old);

    new = old;

    new.c_iflag &= ~(BRKINT | ICRNL | INLCR | IGNCR | INPCK | ISTRIP | IXON);
    new.c_oflag &= ~OPOST;
    new.c_lflag &= ~(ECHO | ECHOE | ECHONL | ICANON | IEXTEN | ISIG);
    new.c_cflag &= ~(PARENB | CSIZE);
    new.c_cflag |= CS8;

    new.c_cc[VMIN]  = 1;
    new.c_cc[VTIME] = 0;

    tcsetattr(fd, TCSANOW, &new);

    return old;
}

pid_t fork_pty(int fd_master) {
    int fd_slave;
    struct termios termios_slave;
    pid_t pid;

    termios_slave = set_tty_raw(STDIN_FILENO);

    if ((pid = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == (pid_t)0) {
        if (setsid() == -1) {
            perror("setsid");
            exit(EXIT_FAILURE);
        }

        fd_slave = open_slave(fd_master);

        ioctl(fd_slave, TIOCSCTTY, (char *)0);

        if (close(fd_master) == -1) {
            perror("close");
            exit(EXIT_FAILURE);
        }

        tcsetattr(fd_slave, TCSANOW, &termios_slave);

        dup2(fd_slave, STDIN_FILENO);
        dup2(fd_slave, STDOUT_FILENO);
        dup2(fd_slave, STDERR_FILENO);

        if (fd_slave > STDERR_FILENO) {
            if (close(fd_slave) == -1) {
                perror("close");
                exit(EXIT_FAILURE);
            }
        }

        return 0;
    } else {
        return pid;
    }
}

void loop(int rfd1, int wfd1, int rfd2, int wfd2, pid_t pid) {
    int nbytes;
    char buf[1024];
    fd_set rfd_set;

    while (1) {
        FD_ZERO(&rfd_set);
        FD_SET(rfd1, &rfd_set);
        FD_SET(rfd2, &rfd_set);

        if (select(((rfd1 > rfd2 ? rfd1 : rfd2) + 1), &rfd_set, NULL, NULL, NULL) == -1) {
            perror("select");
            exit(EXIT_FAILURE);
        }

        if (FD_ISSET(rfd1, &rfd_set)) {
            if ((nbytes = read(rfd1, buf, sizeof(buf))) == -1) {
                kill(pid, SIGHUP);
                exit(EXIT_FAILURE);
            }

            if (write(wfd1, buf, nbytes) == -1) {
                perror("write");
                exit(EXIT_FAILURE);
            }
        }

        if (FD_ISSET(rfd2, &rfd_set)) {
            if ((nbytes = read(rfd2, buf, sizeof(buf))) == -1) {
                perror("read");
                exit(EXIT_FAILURE);
            }

            if (write(wfd2, buf, nbytes) == -1) {
                perror("write");
                exit(EXIT_FAILURE);
            }
        }
    }
}

int main(int argc, char **argv) {
    int fd_master = open_master();
    pid_t pid;

    if (argc != 2) {
        fputs("Require 1 argument\n", stderr);
        exit(EXIT_FAILURE);
    }

    if ((pid = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (pid == (pid_t)0) {
        execvp(argv[1], &argv[1]);
    } else {
        loop(STDIN_FILENO, fd_master, fd_master, STDOUT_FILENO, pid);
    }

    return 0;
}
