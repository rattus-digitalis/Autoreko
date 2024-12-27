#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/socket.h>
#include <pthread.h>
#include <stdarg.h>

FILE *output_file = NULL;

int is_ipv4_address(const char *input) {
    struct sockaddr_in sa;
    return inet_pton(AF_INET, input, &(sa.sin_addr)) != 0;
}

int is_ipv6_address(const char *input) {
    struct sockaddr_in6 sa6;
    return inet_pton(AF_INET6, input, &(sa6.sin6_addr)) != 0;
}

void write_to_file(const char *format, ...) {
    if (output_file) {
        va_list args;
        va_start(args, format);
        vfprintf(output_file, format, args);
        va_end(args);
    }
}

void execute_command(const char *title, const char *command) {
    printf("\n===== %s =====\n", title);
    write_to_file("\n===== %s =====\n", title);

    FILE *cmd_pipe = popen(command, "r");
    if (!cmd_pipe) {
        fprintf(stderr, "Error executing command: %s\n", command);
        write_to_file("Error executing command: %s\n", command);
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), cmd_pipe) != NULL) {
        printf("%s", buffer);
        write_to_file("%s", buffer);
    }
    pclose(cmd_pipe);
}

void *perform_dns_lookup(void *hostname) {
    char command[256];
    snprintf(command, sizeof(command), "nslookup %s", (char *)hostname);
    execute_command("DNS Lookup", command);
    pthread_exit(NULL);
}

void *perform_scan(void *args) {
    char **params = (char **)args;
    const char *type = params[0];
    const char *target = params[1];
    char command[256];

    if (strcmp(type, "Light") == 0) {
        snprintf(command, sizeof(command), "nmap -sP %s", target);
        execute_command("Light Scan", command);
    } else if (strcmp(type, "Medium") == 0) {
        if (geteuid() != 0) {
            fprintf(stderr, "Medium scan requires root privileges.\n");
            write_to_file("Medium scan requires root privileges.\n");
            pthread_exit(NULL);
        }
        snprintf(command, sizeof(command), "nmap -v -sS %s", target);
        execute_command("Medium Scan", command);
    } else if (strcmp(type, "Hard") == 0) {
        if (geteuid() != 0) {
            fprintf(stderr, "Hard scan requires root privileges.\n");
            write_to_file("Hard scan requires root privileges.\n");
            pthread_exit(NULL);
        }
        snprintf(command, sizeof(command), "nmap -A -sV %s", target);
        execute_command("Hard Scan", command);
    } else if (strcmp(type, "Hard Full") == 0) {
        if (geteuid() != 0) {
            fprintf(stderr, "Hard Full scan requires root privileges.\n");
            write_to_file("Hard Full scan requires root privileges.\n");
            pthread_exit(NULL);
        }
        snprintf(command, sizeof(command), "nmap -v -A -sV -p- %s", target);
        execute_command("Hard Full Scan", command);
    }
    pthread_exit(NULL);
}

void *validate_ip(void *input) {
    const char *ip = (char *)input;
    printf("\n===== IP Validation =====\n");
    write_to_file("\n===== IP Validation =====\n");

    if (is_ipv4_address(ip)) {
        printf("%s is a valid IPv4 address.\n", ip);
        write_to_file("%s is a valid IPv4 address.\n", ip);
    } else if (is_ipv6_address(ip)) {
        printf("%s is a valid IPv6 address.\n", ip);
        write_to_file("%s is a valid IPv6 address.\n", ip);
    } else {
        printf("%s is not a valid IP address.\n", ip);
        write_to_file("%s is not a valid IP address.\n", ip);
    }
    pthread_exit(NULL);
}

void perform_fuzzing(const char *wordlist_path) {
    char command[256];
    snprintf(command, sizeof(command), "ffuf -w %s -u TARGET_URL", wordlist_path);
    execute_command("Fuzzing with Wordlist", command);
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

int main(int argc, char *argv[]) {
    char input[100] = {0};
    int intensity_choice = 0;
    char output_file_path[256] = {0};
    char url[256] = {0};
    char wordlist_path[256] = {0};

    printf("          _    _ _______ ____         _____      _     ___  \n");
    printf("     /\\  | |  | |__   __/ __ \\       |  __ \\    | |   / _ \\ \n");
    printf("    /  \\\ | |  | |  | | | |  | |______| |__) |___| | _| | | |\n");
    printf("   / /\\ \\\| |  | |  | | | |  | |______|  _  // _ \\\ |/ / | | |\n");
    printf("  / ____ \\\ |__| |  | | | |__| |      | | \\\ \\\  __/   <| |_| |\n");
    printf(" /_/    \\\\\\____/   |_|  \\\\____/       |_|  \\\\\\\___|_|\\_\\\\___/ \n");
    printf("                                                            \n");
    printf("                                                            \n");

    int opt;
    while ((opt = getopt(argc, argv, "ht:i:u:o:W:")) != -1) {
        switch (opt) {
            case 'h':
                print_help();
                return 0;
            case 't':
                strncpy(input, optarg, sizeof(input) - 1);
                break;
            case 'i':
                intensity_choice = atoi(optarg);
                if (intensity_choice < 1 || intensity_choice > 4) {
                    fprintf(stderr, "Invalid intensity choice. Must be between 1 and 4.\n");
                    return 1;
                }
                break;
            case 'u':
                strncpy(url, optarg, sizeof(url) - 1);
                break;
            case 'o':
                strncpy(output_file_path, optarg, sizeof(output_file_path) - 1);
                break;
            case 'W':
                strncpy(wordlist_path, optarg, sizeof(wordlist_path) - 1);
                break;
            default:
                print_help();
                return 1;
        }
    }

    if (strlen(input) == 0) {
        printf("Enter the target (IP or domain): ");
        scanf(" %99s", input);
    }

    if (intensity_choice == 0) {
        printf("Choose scan intensity:\n");
        printf("1 - Light (ping scan)\n");
        printf("2 - Medium (stealth scan)\n");
        printf("3 - Hard (aggressive scan)\n");
        printf("4 - Hard Full (all ports aggressive scan)\n");
        printf("Enter your choice (1/2/3/4): ");
        scanf(" %d", &intensity_choice);
        if (intensity_choice < 1 || intensity_choice > 4) {
            fprintf(stderr, "Invalid choice. Defaulting to Light scan.\n");
            intensity_choice = 1;
        }
    }

    if (intensity_choice >= 2 && geteuid() != 0) {
        fprintf(stderr, "Error: Scan intensity level %d requires root privileges.\n", intensity_choice);
        return 1;
    }

    if (strlen(output_file_path) == 0) {
        printf("Enter the output file path (leave empty for no file): ");
        getchar();
        fgets(output_file_path, sizeof(output_file_path), stdin);
        output_file_path[strcspn(output_file_path, "\n")] = 0;
    }

    if (strlen(output_file_path) > 0) {
        output_file = fopen(output_file_path, "w");
        if (!output_file) {
            fprintf(stderr, "Error: Unable to open file %s for writing.\n", output_file_path);
            return 1;
        }
    }

    if (strlen(wordlist_path) > 0) {
        printf("\nUsing wordlist: %s\n", wordlist_path);
        perform_fuzzing(wordlist_path);
    }

    printf("\nLaunching tests for target: %s with intensity level %d\n", input, intensity_choice);
    write_to_file("\nLaunching tests for target: %s with intensity level %d\n", input, intensity_choice);

    pthread_t dns_thread, scan_thread, ip_thread;
    pthread_create(&dns_thread, NULL, perform_dns_lookup, (void *)input);
    pthread_create(&ip_thread, NULL, validate_ip, (void *)input);

    char *scan_args[2];
    scan_args[1] = input;

    switch (intensity_choice) {
        case 1:
            scan_args[0] = "Light";
            break;
        case 2:
            scan_args[0] = "Medium";
            break;
        case 3:
            scan_args[0] = "Hard";
            break;
        case 4:
            scan_args[0] = "Hard Full";
            break;
    }
    pthread_create(&scan_thread, NULL, perform_scan, scan_args);

    pthread_join(dns_thread, NULL);
    pthread_join(scan_thread, NULL);
    pthread_join(ip_thread, NULL);

    if (output_file) {
        fclose(output_file);
        printf("Results saved to %s\n", output_file_path);
    }

    printf("All tests completed.\n");
    return 0;
}
