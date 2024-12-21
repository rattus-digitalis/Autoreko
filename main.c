#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

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

void scan_with_nmap(const char *target) {
    char command[128];
    snprintf(command, sizeof(command), "nmap %s", target); 
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
    scanf(" %99s", input); 
    printf("You entered: %s\n", input);


    analyze_input(input);
}

int main() {
    ask_and_display_char();
    return 0;
}
