#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "scan.h"
#include "ui.h"

int main(int argc, char *argv[]) {
    char target[256];
    int intensity = 0;

    displayAsciiArt();


    if (argc == 2 && strcmp(argv[1], "-h") == 0) {
        displayHelp();
        return 0;
    }

    if (argc == 2 && strcmp(argv[1], "-t") == 0) {
        askForTarget(target, sizeof(target));
        if (is_service_accessible(target)) {
            printf("The service at '%s' is accessible.\n", target);
        } else {
            printf("The service at '%s' is NOT accessible.\n", target);
        }
        return 0;
    }

    if (argc == 1) {
        askForTarget(target, sizeof(target));
        intensity = chooseScanIntensity();


        printf("Performing scan with intensity %d...\n", intensity);
        if (perform_nmap_scan(target, intensity)) {
            printf("Scan completed successfully.\n");
        } else {
            printf("Scan failed.\n");
        }
        return 0;
    }

    printf("Error: Invalid usage. Use -h for help.\n");
    return 1;
}
