#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fuzzing.h"

void execute_command(char * str, char * text);

void perform_fuzzing(const char *wordlist_path) {
    char command[256];
    snprintf(command, sizeof(command), "ffuf -w %s -u TARGET_URL", wordlist_path);
    execute_command("Fuzzing with Wordlist", command);
}
