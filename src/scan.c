#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scan.h"
#include "utils.h"

int perform_nmap_scan(const char *target, int intensity) {
    char command[512];


    switch (intensity) {
        case 1:
            snprintf(command, sizeof(command), "nmap -sn %s", target); // Scan léger
        break;
        case 2:
            snprintf(command, sizeof(command), "nmap -F %s", target); // Scan rapide
        break;
        case 3:
            snprintf(command, sizeof(command), "nmap -T4 -A %s", target); // Scan par défaut
        break;
        case 4:
            snprintf(command, sizeof(command), "nmap -T4 -A -p- %s", target); // Scan intensif
        break;
        default:
            printf("Error: Invalid scan intensity.\n");
        return 0;
    }


    printf("Running command: %s\n", command);
    int result = system(command);
    return (result == 0);
}

int is_service_accessible(const char *input) {
    char command[512];
    int result;

    if (is_ipv4(input) || is_ipv6(input)) {

        snprintf(command, sizeof(command), "ping -c 1 %s > /dev/null 2>&1", input);
    } else if (is_url(input)) {
        snprintf(command, sizeof(command), "curl -Is %s > /dev/null 2>&1", input);
    } else {
        return 0;
    }

    result = system(command);
    return (result == 0);
}