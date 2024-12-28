#ifndef UI_H
#define UI_H

void displayAsciiArt();
void displayHelp();
void writeOutput(const char *filename, const char *result);
int chooseScanIntensity();
void askForTarget(char *buffer, size_t bufferSize);
int chooseScanType();

#endif // UI_H
