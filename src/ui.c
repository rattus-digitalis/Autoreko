#include <stdio.h>
#include "ui.h"

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
