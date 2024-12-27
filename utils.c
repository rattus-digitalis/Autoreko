#include <stdio.h>
#include <arpa/inet.h>
#include "utils.h"
#include <string.h>


int is_ipv4_address(const char *input) {
    struct sockaddr_in sa;
    return inet_pton(AF_INET, input, &(sa.sin_addr)) != 0;
}


int is_ipv6_address(const char *input) {
    struct sockaddr_in6 sa6;
    return inet_pton(AF_INET6, input, &(sa6.sin6_addr)) != 0;
}


void print_help() {
    printf("Usage:\n");
    printf("  -h            Display this help message\n");
    printf("  -t <Target>   Specify the target IP or domain\n");
    printf("  -i <Intensity>  Specify the scan intensity (1-4)\n");
    printf("  -u <URL>       Specify the URL to validate\n");
    printf("  -o <File>      Specify the output file\n");
    printf("  -W <Wordlist>  Specify the wordlist for fuzzing\n");
}


void pthread_exit(void * p);
FILE *output_file = NULL;

void configure_output_file(const char *output_file_path) {
    if (strlen(output_file_path) > 0) {
        output_file = fopen(output_file_path, "w");
        if (!output_file) {
            perror("Erreur à l'ouverture du fichier de sortie");
        }
    }
}


void *validate_ip(void *input) {
    const char *ip = (char *)input;
    printf("\n===== IP Validation =====\n");
    if (is_ipv4_address(ip)) {
        printf("%s is a valid IPv4 address.\n", ip);
    } else if (is_ipv6_address(ip)) {
        printf("%s is a valid IPv6 address.\n", ip);
    } else {
        printf("%s is not a valid IP address.\n", ip);
    }
    pthread_exit(NULL);
}
