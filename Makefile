CC = gcc
CFLAGS = -Wall -Wextra -g
SRC = src/main.c src/utils.c src/scan.c src/ui.c
OBJ = $(SRC:.c=.o)
EXEC = autoreko

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)
