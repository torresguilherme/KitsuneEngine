CC = g++
CFLAGS = -no-pie -g3 -std=c++17
SRC = main.cpp display.cpp game.cpp input.cpp
BIN = exec

GL_LINKS = -lGL -lGLEW -lSDL2

DB = gdb
VFLAGS = valgrind -v --show-leak-kinds=all --track-origins=yes --leak-check=full

all: FORCE
	$(CC) $(CFLAGS) $(SRC) -o $(BIN) $(GL_LINKS)
run:
	./$(BIN)
test: all run

valgrind: all
	$(VFLAGS) ./$(BIN)
FORCE:

