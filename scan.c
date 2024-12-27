#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scan.h"

void pthread_exit(void * p);

void *perform_scan(void *args) {
    char **params = (char **)args;
    const char *type = params[0];
    const char *target = params[1];
    char command[256];

    if (strcmp(type, "Light") == 0) {
        snprintf(command, sizeof(command), "nmap -sP %s", target);
    } else if (strcmp(type, "Medium") == 0) {
        snprintf(command, sizeof(command), "nmap -v -sS %s", target);
    } else if (strcmp(type, "Hard") == 0) {
        snprintf(command, sizeof(command), "nmap -A -sV %s", target);
    } else if (strcmp(type, "Hard Full") == 0) {
        snprintf(command, sizeof(command), "nmap -v -A -sV -p- %s", target);
    }

    execute_command("Scan", command);
    pthread_exit(NULL);
}

void execute_command(const char *title, const char *command) {
    printf("\n===== %s =====\n", title);
    FILE *cmd_pipe = popen(command, "r");
    if (!cmd_pipe) {
        fprintf(stderr, "Error executing command: %s\n", command);
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), cmd_pipe) != NULL) {
        printf("%s", buffer);
    }
    pclose(cmd_pipe);
}
