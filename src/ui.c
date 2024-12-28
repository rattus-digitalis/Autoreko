#include <stdio.h>
#include "ui.h"
#include <string.h>

void displayAsciiArt() {
    FILE *file = fopen("ascii.txt", "r");
    if (file == NULL) {
        perror("Error opening ASCII art file");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }

    fclose(file);
}

void displayHelp() {
    printf("Usage: ./autoreko [OPTIONS] [INPUT]\n");
    printf("Options:\n");
    printf("  -t <ip/url>   Test if the service at the IP or URL is accessible\n");
    printf("  -o <file>     Output the result to the specified file\n");
    printf("  -i            Prompt the user to choose the scan intensity interactively\n");
    printf("                 Offers choices from:\n");
    printf("                   1: Light scan \n");
    printf("                   2: Fast scan \n");
    printf("                   3: Default scan \n");
    printf("                   4: Intensive scan with all ports\n");
    printf("  -h            Display this help message\n");
    printf("\n");
    printf("If no options are provided, the program will ask for a target and intensity.\n");
}


int chooseScanIntensity() {
    int intensity = 0;
    while (intensity < 1 || intensity > 4) {
        printf("Select Nmap Scan Intensity:\n");
        printf("  1. Light scan \n");
        printf("  2. Fast scan \n");
        printf("  3. Default scan \n");
        printf("  4. Intensive scan with all ports \n");
        printf("Enter the intensity level (1-4): ");
        if (scanf("%d", &intensity) != 1) {
            while (getchar() != '\n'); // Clear invalid input
            intensity = 0;
            printf("Invalid input. Please enter a number between 1 and 4.\n");
        }
    }
    return intensity;
}

void askForTarget(char *buffer, size_t bufferSize) {
    printf("Enter the target IP or URL for the scan: ");
    fgets(buffer, bufferSize, stdin);
    buffer[strcspn(buffer, "\n")] = '\0'; // Remove trailing newline
}