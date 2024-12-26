CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude  # Add -Iinclude to tell the compiler to look in the include directory

SRC = src/main.c src/shell.c
OBJ = src/main.o src/shell.o
BIN = bin/myshell

all: $(BIN)

$(BIN): $(OBJ)
	$(CC) $(OBJ) -o $(BIN)

src/main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o src/main.o

src/shell.o: src/shell.c
	$(CC) $(CFLAGS) -c src/shell.c -o src/shell.o

run: $(BIN)
	./$(BIN)

clean:
	rm -f $(OBJ) $(BIN)
