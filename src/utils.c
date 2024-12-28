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
    int result;

    // Regex pour valider les URL basiques
    const char *pattern = "^(https?://)?([a-zA-Z0-9.-]+)(:[0-9]+)?(/.*)?$";

    // Compile le regex
    if (regcomp(&regex, pattern, REG_EXTENDED | REG_NOSUB) != 0) {
        return 0; // Erreur dans la compilation du regex
    }

    // Exécute le regex
    result = regexec(&regex, input, 0, NULL, 0);
    regfree(&regex);

    return (result == 0); // Retourne 1 si l'URL est valide
}
