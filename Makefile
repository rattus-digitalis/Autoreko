CC = gcc
CFLAGS = -Wall -Wextra -g
SRC = src/main.c src/utils.c src/scan.c src/ui.c
OBJ = $(SRC:.c=.o)
EXEC = autoreko

# Répertoires d'installation
PREFIX = /usr/local
BINDIR = $(PREFIX)/bin
DOCDIR = $(PREFIX)/share/doc/$(EXEC)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)

install: all
	# Crée les répertoires d'installation si nécessaires
	mkdir -p $(BINDIR)
	mkdir -p $(DOCDIR)
	# Copie le binaire
	install -m 0755 $(EXEC) $(BINDIR)
	# Copie la documentation (README.md, LICENSE, etc.)
	install -m 0644 README.md LICENSE $(DOCDIR)

uninstall:
	# Supprime les fichiers installés
	rm -f $(BINDIR)/$(EXEC)
	rm -rf $(DOCDIR)

.PHONY: all clean install uninstall
