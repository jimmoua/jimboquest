CC=gcc

SRC_DIR=src

SRC_EXT=cc

INCLUDE_DIR=include

OBJ_DIR=obj

BIN_DIR=bin

CFLAGS=-lstdc++ \
			 -std=c++17 \
			 -lsfml-graphics \
			 -lsfml-system \
			 -lsfml-window \
			 -lsfml-audio \
			 -lpthread \
			 -lX11 \
			 -g

WFLAGS=-Wall \
			 -Wextra \
			 -g

EXE=jimboQuest.out

SOURCES := $(wildcard $(SRC_DIR)/*.$(SRC_EXT))
OBJECTS := $(SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/%.o)

all: $(OBJECTS)
	@mkdir -p bin
	$(CC) $(OBJECTS) $(CFLAGS) -o $(BIN_DIR)/$(EXE)

$(OBJECTS): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.$(SRC_EXT)
	@mkdir -p obj
	$(CC) $(WFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	rm $(OBJECTS) $(BIN_DIR)/$(EXE) -v

run:
	./$(BIN_DIR)/$(EXE)
