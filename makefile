CC = g++
LIBS = -lfreeimage
CFLAGS = -std=c++11 -g

SRC_DIR = ./src
OBJ_DIR = ./obj
BIN_DIR = ./bin

SRC = $(shell find $(SRC_DIR) -name \*.cpp)
_OBJECTS = $(subst $(SRC_DIR), $(OBJ_DIR), $(SRC))
OBJECTS = $(_OBJECTS:%.cpp=%.o)

.PHONY: clean

# TODO: add header file dependencies

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) -c -o $@ $(CFLAGS) $<

$(BIN_DIR)/client.out: $(OBJECTS)
	@mkdir -p $(@D)
	$(CC) -o $@ $^ $(LIBS)

clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR)
