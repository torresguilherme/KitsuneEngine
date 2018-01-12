BIN = exec
DB = gdb
VFLAGS = valgrind -v --show-leak-kinds=all --track-origins=yes --leak-check=full

all: 
	@./compile.sh
clean:
	@./compile.sh clean
run:
	./$(BIN)
test: all run

valgrind: all
	$(VFLAGS) ./$(BIN)
FORCE:

