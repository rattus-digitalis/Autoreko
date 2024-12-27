#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include "scan.h"
#include "fuzzing.h"
#include "utils.h"
#include "ui.h"

FILE *output_file = NULL;

int main(int argc, char *argv[]) {
    // Déclaration des variables
    char input[100] = {0};
    int intensity_choice = 0;
    char output_file_path[256] = {0};
    char url[256] = {0};
    char wordlist_path[256] = {0};

    // Affichage du logo
    display_logo();

    // Traitement des arguments de la ligne de commande
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

    // Validation et configuration des variables
    if (strlen(input) == 0) {
        printf("Enter the target (IP or domain): ");
        scanf(" %99s", input);
    }

    // Configuration des permissions et du fichier de sortie
    configure_output_file(output_file_path);
    validate_input(intensity_choice, input);

    // Exécution des tests
    if (strlen(wordlist_path) > 0) {
        perform_fuzzing(wordlist_path);
    }

    perform_tests(input, intensity_choice);

    // Fermeture du fichier de sortie
    if (output_file) {
        fclose(output_file);
        printf("Results saved to %s\n", output_file_path);
    }

    return 0;
}
