#ifndef UTILS_H
#define UTILS_H

// Déclaration des fonctions pour valider les adresses IP
int is_ipv4_address(const char *input);
int is_ipv6_address(const char *input);

// Déclaration de la fonction de validation d'adresse IP dans un thread
void *validate_ip(void *input);

// Déclaration de la fonction d'affichage de l'aide
void print_help(void);

#endif // UTILS_H
//
// Created by rattus on 27/12/24.
//
