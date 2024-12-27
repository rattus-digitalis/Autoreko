#ifndef SCAN_H
#define SCAN_H

// Déclaration de la fonction pour exécuter une commande (nmap, etc.)
void execute_command(const char *title, const char *command);

// Déclaration de la fonction de scan dans un thread
void *perform_scan(void *args);

#endif // SCAN_H
