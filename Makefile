SRC=$(wildcard src/*.cpp)
FLAGS=-Wall -Werror -Wextra -I inc

BIN_DIR=bin

all:
	@mkdir -p $(BIN_DIR)
	g++ $(FLAGS) $(SRC) -o $(BIN_DIR)/start.out

rebuild: clean all
	$(BIN_DIR)/start.out

clean:
	rm -rf $(BIN_DIR)
	clear
