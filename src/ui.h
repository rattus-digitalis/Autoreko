#ifndef UI_H
#define UI_H

void displayAsciiArt();
void displayHelp();
void writeOutput(const char *filename, const char *result);
int chooseScanIntensity();
void askForTarget(char *buffer, size_t bufferSize);

#endif // UI_H
