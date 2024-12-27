#ifndef UI_H
#define UI_H

void displayAsciiArt();
void displayHelp();
void writeOutput(const char *filename, const char *result);
/**
 * Demande à l'utilisateur de choisir une intensité.
 * @return L'intensité choisie (1 à 4).
 */
int chooseScanIntensity();
/**
 * Demande à l'utilisateur une cible.
 * @param buffer Buffer où la cible sera stockée.
 * @param bufferSize Taille du buffer.
 */
void askForTarget(char *buffer, size_t bufferSize);

#endif // UI_H
