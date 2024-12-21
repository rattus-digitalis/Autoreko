#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h> // Pour system()

int is_ipv4_address(const char *input) {
    int dots = 0;
    const char *ptr = input;

    while (*ptr) {
        if (*ptr == '.') {
            dots++;
        } else if (!isdigit(*ptr)) {
            return 0; // Non numérique et pas un point
        }
        ptr++;
    }
    return dots == 3; // Une IPv4 doit avoir exactement 3 points
}

int is_ipv6_address(const char *input) {
    int colons = 0;
    const char *ptr = input;

    while (*ptr) {
        if (*ptr == ':') {
            colons++;
        } else if (!isxdigit(*ptr)) {
            return 0; // Non héxadécimal et pas un double point
        }
        ptr++;
    }
    return colons >= 2 && colons <= 7; // Une IPv6 doit avoir entre 2 et 7 double points
}

void scan_with_nmap(const char *target) {
    char command[128];
    snprintf(command, sizeof(command), "nmap %s", target); // Commande Nmap pour scanner la cible
    int result = system(command);
    if (result != 0) {
        printf("Nmap scan failed.\n");
    }
}

void analyze_input(const char *input) {
    if (is_ipv4_address(input)) {
        printf("The input is a valid IPv4 address.\n");
        scan_with_nmap(input);
    } else if (is_ipv6_address(input)) {
        printf("The input is a valid IPv6 address.\n");
        scan_with_nmap(input);
    } else {
        printf("The input is not a valid IPv4 or IPv6 address.\n");
    }
}

void ask_and_display_char() {
    char input[100];

    printf("Enter the target: ");
    scanf(" %99s", input); // Lecture de la chaîne avec une limite de 99 caractères
    printf("You entered: %s\n", input);

    // Analyse de l'entrée
    analyze_input(input);
}

int main() {
    ask_and_display_char();
    return 0;
}
