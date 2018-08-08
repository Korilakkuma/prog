#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>

int main(int argc, char **argv) {
    struct hostent *hp;

    if (argc != 2) {
        fputs("Require hostname\n", stderr);
        exit(EXIT_FAILURE);
    }

    if ((hp = gethostbyname(argv[1])) == NULL) {
        herror("gethostbyname");
        exit(EXIT_FAILURE);
    }

    printf("h_name      %s\n", hp->h_name);
    printf("h_aliases   %s\n", *hp->h_aliases);
    printf("h_addrtype  %d\n", hp->h_addrtype);
    printf("h_length    %d\n", hp->h_length);
    printf("h_addr_list %s\n", *hp->h_addr_list);

    return 0;
}
