# Variables
CC = gcc
CFLAGS = -Wall -Wextra -g
SRC_DIR = src
SRC = $(SRC_DIR)/main.c $(SRC_DIR)/ui.c
OBJ = $(SRC:.c=.o)
EXEC = autoreko

# Règle principale
all: $(EXEC)

# Lien de l'exécutable
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $@

# Compilation des fichiers .o à partir des .c
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage
clean:
	rm -f $(OBJ) $(EXEC)
