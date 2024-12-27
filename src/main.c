#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utils.h"
#include "scan.h"
#include "ui.h"

int main(int argc, char *argv[]) {
    char target[256];
    int intensity = 0;

    // Affiche l'art ASCII
    displayAsciiArt();

    // Gestion de l'aide
    if (argc == 2 && strcmp(argv[1], "-h") == 0) {
        displayHelp();
        return 0;
    }

    // Gestion de l'option -t
    if (argc == 2 && strcmp(argv[1], "-t") == 0) {
        askForTarget(target, sizeof(target));
        if (is_service_accessible(target)) {
            printf("The service at '%s' is accessible.\n", target);
        } else {
            printf("The service at '%s' is NOT accessible.\n", target);
        }
        return 0;
    }

    // Si aucune option n'est spécifiée
    if (argc == 1) {
        askForTarget(target, sizeof(target));  // Demande la cible
        intensity = chooseScanIntensity();    // Demande l'intensité

        // Effectue le scan avec l'intensité choisie
        printf("Performing scan with intensity %d...\n", intensity);
        if (perform_nmap_scan(target, intensity)) {
            printf("Scan completed successfully.\n");
        } else {
            printf("Scan failed.\n");
        }
        return 0;
    }

    // Si une option non reconnue est spécifiée
    printf("Error: Invalid usage. Use -h for help.\n");
    return 1;
}
