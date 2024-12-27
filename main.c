#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <pthread.h>

int is_ipv4_address(const char *input) {
    struct sockaddr_in sa;
    return inet_pton(AF_INET, input, &(sa.sin_addr)) != 0;
}

int is_ipv6_address(const char *input) {
    struct sockaddr_in6 sa6;
    return inet_pton(AF_INET6, input, &(sa6.sin6_addr)) != 0;
}

void *perform_dns_lookup(void *hostname) {
    struct hostent *host;
    struct in_addr **addr_list;

    printf("Starting DNS Lookup...\n");

    if ((host = gethostbyname((char *)hostname)) == NULL) {
        printf("DNS lookup failed for %s\n", (char *)hostname);
        pthread_exit(NULL);
    }

    addr_list = (struct in_addr **)host->h_addr_list;
    printf("DNS lookup results for %s:\n", (char *)hostname);
    for (int i = 0; addr_list[i] != NULL; i++) {
        printf("  - %s\n", inet_ntoa(*addr_list[i]));
    }

    pthread_exit(NULL);
}

void *perform_light_scan(void *target) {
    char *ip = (char *)target;
    printf("Performing light scan on %s...\n", ip);
    char command[128];
    snprintf(command, sizeof(command), "nmap -sP %s", ip);
    system(command);
    pthread_exit(NULL);
}

void *perform_medium_scan(void *target) {
    if (geteuid() != 0) {
        printf("Medium scan requires sudo privileges. Please run the program as root.\n");
        pthread_exit(NULL);
    }
    char *ip = (char *)target;
    printf("Performing medium scan on %s...\n", ip);
    char command[128];
    snprintf(command, sizeof(command), "nmap -v -sS %s", ip);
    system(command);
    pthread_exit(NULL);
}

void *perform_full_scan(void *target) {
    if (geteuid() != 0) {
        printf("Full scan requires sudo privileges. Please run the program as root.\n");
        pthread_exit(NULL);
    }
    char *ip = (char *)target;
    printf("Performing full scan on %s...\n", ip);
    char command[128];
    snprintf(command, sizeof(command), "nmap -A -p- %s", ip);
    system(command);
    pthread_exit(NULL);
}

void *validate_ip(void *input) {
    char *ip = (char *)input;

    printf("Starting IP validation...\n");

    if (is_ipv4_address(ip)) {
        printf("%s is a valid IPv4 address.\n", ip);
    } else if (is_ipv6_address(ip)) {
        printf("%s is a valid IPv6 address.\n", ip);
    } else {
        printf("%s is not a valid IP address.\n", ip);
    }

    pthread_exit(NULL);
}

int main() {
    char input[100];
    int intensity_choice;
    pthread_t dns_thread, scan_thread, ip_thread;

    printf("          _    _ _______ ____         _____      _     ___  \n");
    printf("     /\\  | |  | |__   __/ __ \\       |  __ \\    | |   / _ \\ \n");
    printf("    /  \\ | |  | |  | | | |  | |______| |__) |___| | _| | | |\n");
    printf("   / /\\ \\| |  | |  | | | |  | |______|  _  // _ \\ |/ / | | |\n");
    printf("  / ____ \\ |__| |  | | | |__| |      | | \\ \\  __/   <| |_| |\n");
    printf(" /_/    \\_\\____/   |_|  \\____/       |_|  \\_\\___|_|\\_\\\\___/ \n");
    printf("                                                            \n");
    printf("                                                            \n");


    printf("Enter the target (IP or domain): ");
    scanf(" %99s", input);

    printf("Choose scan intensity:\n");
    printf("1 - Light (ping scan)\n");
    printf("2 - Medium (stealth scan)\n");
    printf("3 - Full (aggressive scan)\n");
    printf("Enter your choice (1/2/3): ");
    scanf(" %d", &intensity_choice);

    printf("Launching all tests on %s with intensity %d...\n", input, intensity_choice);

    pthread_create(&dns_thread, NULL, perform_dns_lookup, (void *)input);
    pthread_create(&ip_thread, NULL, validate_ip, (void *)input);

    if (intensity_choice == 1) {
        pthread_create(&scan_thread, NULL, perform_light_scan, (void *)input);
    } else if (intensity_choice == 2) {
        pthread_create(&scan_thread, NULL, perform_medium_scan, (void *)input);
    } else if (intensity_choice == 3) {
        pthread_create(&scan_thread, NULL, perform_full_scan, (void *)input);
    } else {
        printf("Invalid choice. Defaulting to Light scan.\n");
        pthread_create(&scan_thread, NULL, perform_light_scan, (void *)input);
    }

    pthread_join(dns_thread, NULL);
    pthread_join(scan_thread, NULL);
    pthread_join(ip_thread, NULL);

    printf("All tests completed.\n");
    return 0;
}
