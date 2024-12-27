# Définition du compilateur et des options
CC = gcc
CFLAGS = -Wall -Wextra -g -pthread

# Répertoire des sources
SRC_DIR = src

# Fichiers sources et objets
SRC_FILES = $(SRC_DIR)/main.c \
            $(SRC_DIR)/utils.c \
            $(SRC_DIR)/scan.c \
            $(SRC_DIR)/fuzzing.c \
            $(SRC_DIR)/ui.c

OBJ_FILES = $(SRC_FILES:$(SRC_DIR)/%.c=$(SRC_DIR)/%.o)

# Nom de l'exécutable
EXEC = autoreko

# Règle par défaut : compiler l'exécutable
all: $(EXEC)

# Lier les fichiers objets pour générer l'exécutable
$(EXEC): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) -o $(EXEC)

# Règle pour compiler chaque fichier .c en .o
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyer les fichiers objets et l'exécutable
clean:
	rm -f $(OBJ_FILES) $(EXEC)

# Affichage d'une aide simple
help:
	@echo "Makefile pour le projet autoreko"
	@echo "Utilisez 'make' pour compiler le projet."
	@echo "Utilisez 'make clean' pour nettoyer les fichiers objets et l'exécutable."
