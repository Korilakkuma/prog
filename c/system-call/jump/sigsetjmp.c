#include <setjmp.h>
#include <signal.h>
#include <stdio.h>

static sigjmp_buf env;

void sig_handler(int sig) {
    fputs("handler\n", stderr);
    siglongjmp(env, 1);
}

int main(void) {
    int dummy;
    int *p = (int *)0x123;

    struct sigaction act;
    sigset_t old_sigset;

    act.sa_handler = sig_handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGSEGV, &act, NULL);
    sigaction(SIGBUS,  &act, NULL);

    if (sigsetjmp(env, 1) == 0) {
        fputs("main(1)\n", stderr);
        dummy = *p;
    }

    fputs("main(2)\n", stderr);

    sigprocmask(SIG_SETMASK, NULL, &old_sigset);

    printf("%d\n", sigismember(&old_sigset, SIGSEGV));

    return 0;
}
