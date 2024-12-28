#include <stdio.h>
#include <string.h>
#include "utils.h"
#include "scan.h"
#include "ui.h"

int main(int argc, char *argv[]) {
    char target[256];
    int scanType = 0;

    displayAsciiArt();

    if (argc == 2 && strcmp(argv[1], "-h") == 0) {
        displayHelp();
        return 0;
    }

    if (argc == 3 && strcmp(argv[1], "-u") == 0) {
        strncpy(target, argv[2], sizeof(target));
        target[sizeof(target) - 1] = '\0'; // Assure la terminaison

        if (!is_url(target)) {
            printf("Error: Invalid URL format.\n");
            return 1;
        }

        printf("Scanning URL: %s\n", target);

        printf("Performing Nmap scan...\n");
        int intensity = chooseScanIntensity();
        if (perform_nmap_scan(target, intensity)) {
            printf("Nmap scan completed successfully.\n");
        } else {
            printf("Nmap scan failed.\n");
        }
        return 0;
    }

    if (argc == 1) {
        printf("Enter the target (IP or URL): ");
        fgets(target, sizeof(target), stdin);
        target[strcspn(target, "\n")] = '\0'; // Remove trailing newline

        if (is_url(target)) {
            printf("Detected URL. Proceeding with URL scan.\n");
        } else if (is_ipv4(target) || is_ipv6(target)) {
            printf("Detected IP address. Proceeding with IP scan.\n");
        } else {
            printf("Error: Invalid target format.\n");
            return 1;
        }

        printf("Performing Nmap scan...\n");
        int intensity = chooseScanIntensity();
        if (perform_nmap_scan(target, intensity)) {
            printf("Nmap scan completed successfully.\n");
        } else {
            printf("Nmap scan failed.\n");
        }
        return 0;
    }

    printf("Error: Invalid usage. Use -h for help.\n");
    return 1;
}
