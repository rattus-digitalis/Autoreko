#include <arpa/inet.h>
#include <regex.h>
#include <stddef.h> // Inclure pour NULL
#include "utils.h"

int is_ipv4(const char *input) {
    struct sockaddr_in sa;
    return inet_pton(AF_INET, input, &(sa.sin_addr)) == 1;
}

int is_ipv6(const char *input) {
    struct sockaddr_in6 sa6;
    return inet_pton(AF_INET6, input, &(sa6.sin6_addr)) == 1;
}

int is_url(const char *input) {
    regex_t regex;
    int reti;

    const char *pattern = "^(https?://)?([a-zA-Z0-9.-]+)(:[0-9]+)?(/.*)?$";
    reti = regcomp(&regex, pattern, REG_EXTENDED | REG_ICASE);
    if (reti) {
        return 0;
    }

    reti = regexec(&regex, input, 0, NULL, 0);
    regfree(&regex);

    return reti == 0;
}
