#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Function to check if the input is a valid IPv4 address
int is_ipv4_address(const char *input) {
    int dots = 0;
    const char *ptr = input;

    while (*ptr) {
        if (*ptr == '.') {
            dots++;
        } else if (!isdigit(*ptr)) {
            return 0;
        }
        ptr++;
    }
    return dots == 3;
}

// Function to check if the input is a valid IPv6 address
int is_ipv6_address(const char *input) {
    int colons = 0;
    const char *ptr = input;

    while (*ptr) {
        if (*ptr == ':') {
            colons++;
        } else if (!isxdigit(*ptr)) {
            return 0;
        }
        ptr++;
    }
    return colons >= 2 && colons <= 7;
}

// Function to scan a target using nmap with the specified scan level
void scan_with_nmap(const char *target, const char *level) {
    char command[256];

    if (strcmp(level, "soft") == 0) {
        snprintf(command, sizeof(command), "nmap -sP %s", target);
    } else if (strcmp(level, "medium") == 0) {
        snprintf(command, sizeof(command), "nmap -sS %s", target);
    } else if (strcmp(level, "hard") == 0) {
        snprintf(command, sizeof(command), "nmap -A -sV   %s", target);
    } else {
        printf("Invalid scan level. Defaulting to soft scan.\n");
        snprintf(command, sizeof(command), "nmap -sP %s", target);
    }

    int result = system(command);
    if (result != 0) {
        printf("Nmap scan failed.\n");
    }
}

// Function to analyze the input and perform the scan
void analyze_input(const char *input, const char *level) {
    if (is_ipv4_address(input)) {
        printf("The input is a valid IPv4 address.\n");
        scan_with_nmap(input, level);
    } else if (is_ipv6_address(input)) {
        printf("The input is a valid IPv6 address.\n");
        scan_with_nmap(input, level);
    } else {
        printf("The input is not a valid IPv4 or IPv6 address.\n");
    }
}

// Function to ask for user input and process it
void ask_and_display_char() {
    char input[100];
    int level_choice;
    char *level;

    printf("Enter the target: ");
    scanf(" %99s", input);

    printf("Choose scan level:\n");
    printf("1 - Light (soft scan)\n");
    printf("2 - Medium (stealth scan)\n");
    printf("3 - Hard (aggressive full scan with vulnerability check)\n");
    printf("Enter your choice (1/2/3): ");
    scanf(" %d", &level_choice);

    if (level_choice == 1) {
        level = "soft";
    } else if (level_choice == 2) {
        level = "medium";
    } else if (level_choice == 3) {
        level = "hard";
    } else {
        printf("Invalid choice. Defaulting to Light (soft scan).\n");
        level = "soft";
    }

    printf("You entered: %s\n", input);
    printf("Scan level: %s\n", level);

    analyze_input(input, level);
}

// Main function
int main() {
printf("          _    _ _______ ____         _____      _     ___  \n");
printf("     /\\  | |  | |__   __/ __ \\       |  __ \\    | |   / _ \\ \n");
printf("    /  \\ | |  | |  | | | |  | |______| |__) |___| | _| | | |\n");
printf("   / /\\ \\| |  | |  | | | |  | |______|  _  // _ \\ |/ / | | |\n");
printf("  / ____ \\ |__| |  | | | |__| |      | | \\ \\  __/   <| |_| |\n");
printf(" /_/    \\_\\____/   |_|  \\____/       |_|  \\_\\___|_|\\_\\\\___/ \n");
printf("                                                            \n");
printf("                                                            \n");



    printf("Bienvenue dans le programme !\n");
    ask_and_display_char();
    return 0;
}

