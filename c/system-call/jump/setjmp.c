#include <setjmp.h>
#include <stdio.h>
#include <unistd.h>

static jmp_buf env;

static void print_i(int i) {
    fprintf(stderr, "%d ", i);

    if (i >= 5) {
        fputc('\n', stdout);
        longjmp(env, i);
    }
}

int main(void) {
    int i;

    setjmp(env);

    i = 0;

    while (1) {
        print_i(i);
        sleep(1);
        i++;
    }

    return 0;
}
