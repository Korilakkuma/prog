#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <signal.h>
#include <curses.h>
#include "../lib/lib.h"

#define BUF_LEN 80

#define SEND_WIN_WIDTH  60
#define SEND_WIN_HEIGHT  1

#define RECV_WIN_WIDTH  60
#define RECV_WIN_HEIGHT 13

static WINDOW *win_send, *win_recv;
static WINDOW *frame_send, *frame_recv;

static char send_buf[BUF_LEN];
static char recv_buf[BUF_LEN];
static int session_soc;
static fd_set mask;
static int width;

static void die();

void session_init(int soc) {
    char buf[BUF_LEN];

    if (read(soc, buf, BUF_LEN) == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    fputs(buf, stderr);

    memset(buf, 0, BUF_LEN);

    fgets(buf, BUF_LEN, stdin);
    chop_newline(buf, BUF_LEN);

    if (write(soc, buf, sizeof(buf)) == -1) {
        perror("write");
        exit(EXIT_FAILURE);
    }

    memset(buf, 0, BUF_LEN);

    if (read(soc, buf, BUF_LEN) == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }

    fputs(buf, stderr);

    session_soc = soc;
    width = soc + 1;

    FD_ZERO(&mask);
    FD_SET(STDIN_FILENO, &mask);
    FD_SET(soc, &mask);

    signal(SIGINT, die);

    initscr();

    frame_send = newwin((SEND_WIN_HEIGHT + 2), (SEND_WIN_WIDTH + 2), 18, 0);
    win_send = newwin(SEND_WIN_HEIGHT, SEND_WIN_WIDTH, 19, 1);

    box(frame_send, '|', '-');
    scrollok(win_send, TRUE);
    wmove(win_send, 0, 0);

    frame_recv = newwin((RECV_WIN_HEIGHT + 2), (RECV_WIN_WIDTH + 2), 0, 0);
    win_recv = newwin(RECV_WIN_HEIGHT, RECV_WIN_WIDTH, 1, 1);

    box(frame_recv, '|', '-');
    scrollok(win_recv, TRUE);
    wmove(win_recv, 0, 0);

    cbreak();
    noecho();

    wrefresh(frame_recv);
    wrefresh(win_recv);
    wrefresh(frame_send);
    wrefresh(win_send);
}

void session_loop() {
    int c;
    int flag = 1;
    fd_set read0k;
    int len = 0;
    int i;
    int y, x;
    int n;

    while (flag) {
        read0k = mask;

        if (select(width, (fd_set *)&read0k, NULL, NULL, NULL) < 0) {
            perror("select");
            exit(EXIT_FAILURE);
        }

        if (FD_ISSET(STDIN_FILENO, &read0k)) {
            c = getc(stdin);

            if ((c == '\b') || (c == 0x10) || (c == 0x7F)) {
                if (len == 0) {
                    break;
                }

                len--;

                getyx(win_send, y, x);
                wmove(win_send, y, (x - 1));
                waddch(win_send, ' ');
                wmove(win_send, y, (x - 1));
            } else if ((c == '\n') || (c == '\r')) {
                send_buf[len++] = '\n';

                if (write(session_soc, send_buf, len) == -1) {
                    perror("write");
                    exit(EXIT_FAILURE);
                }

                wclear(win_send);

                len = 0;
            } else {
                send_buf[len++] = c;
                waddch(win_send, c);
            }

            wrefresh(win_send);
        }

        if (FD_ISSET(session_soc, &read0k)) {
            if ((n = read(session_soc, recv_buf, BUF_LEN)) == -1) {
                perror("read");
                exit(EXIT_FAILURE);
            }

            for (i = 0; i < n; i++) {
                waddch(win_recv, recv_buf[i]);
            }

            wrefresh(win_recv);
        }

        if (strstr(recv_buf, "quit") != NULL) {
            flag = 0;

            wrefresh(win_recv);
            wrefresh(win_send);
        }
    }

    die();
}

static void die() {
    endwin();

    if (close(session_soc) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
