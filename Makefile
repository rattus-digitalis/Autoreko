CC = gcc
CFLAGS = -Wall -Wextra -g -pthread
LDFLAGS = -pthread
SRC_FILES = main.c utils.c scan.c fuzzing.c ui.c
OBJ_FILES = $(SRC_FILES:.c=.o)
EXEC = autoreko

all: $(EXEC)

$(EXEC): $(OBJ_FILES)
	$(CC) $(OBJ_FILES) $(LDFLAGS) -o $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_FILES) $(EXEC)

help:
	@echo "Cibles disponibles :"
	@echo "  all    : Compile l'exécutable."
	@echo "  clean  : Nettoie les fichiers objets et l'exécutable."
	@echo "  help   : Affiche cette aide."

.PHONY: all clean help

