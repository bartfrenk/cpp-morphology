CC = clang++
LIBS = -lfreeimage
CFLAGS = -std=c++11 -g

SRC_DIR = ./src
OBJ_DIR = ./obj
BIN_DIR = ./bin

# transforms *.cpp source paths into corresponding *.o binary paths
make_objs = $(patsubst %.cpp,%.o,$(subst $(SRC_DIR), $(OBJ_DIR), $(1)))
find_src = $(shell find ${SRC_DIR}/$(1) -name \*.cpp)

SRC_IMAGE = $(call find_src,image)
OBJ_IMAGE = $(call make_objs,${SRC_IMAGE})

SRC_UTILS = $(call find_src,utils)
OBJ_UTILS = $(call make_objs,${SRC_UTILS})

SRC = $(shell find $(SRC_DIR) -name \*.cpp)
_OBJECTS = $(subst $(SRC_DIR), $(OBJ_DIR), $(SRC))
OBJECTS = $(_OBJECTS:%.cpp=%.o)

.PHONY: clean test

test:
	echo $(SRC_IMAGE)
	echo $(OBJ_IMAGE)

# TODO: add header file dependencies

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CC) -c -o $@ $(CFLAGS) $<

$(BIN_DIR)/test_filter.out: $(OBJECTS)
	@mkdir -p $(@D)
	$(CC) -o $@ $^ $(LIBS)

${BIN_DIR}/test_image.out: ${OBJ_DIR}/test_image.o ${OBJ_IMAGE} ${OBJ_UTILS}
	@mkdir -p ${@D}
	${CC} -o $@ $^ ${LIBS}

clean:
	@rm -rf $(OBJ_DIR) $(BIN_DIR)
