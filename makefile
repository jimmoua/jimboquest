CC=clang++

SRC_DIR=src

SRC_EXT=cc

INCLUDE_DIR=include

OBJ_DIR=obj

# Directory of the executable
BIN_DIR=bin

# Compile flags
CFLAGS= -std=c++11 \
				-lsfml-system \
				-lsfml-window \
				-lsfml-graphics \
				-lsfml-audio \
				-pthread

# Warning flags
WFLAGS= -Wall \
				-Wextra

# Set the name of the project here
EXE=jimboQuest.out

SOURCES := $(wildcard $(SRC_DIR)/*.$(SRC_EXT))
OBJECTS := $(SOURCES:$(SRC_DIR)/%.$(SRC_EXT)=$(OBJ_DIR)/%.o)

all: $(OBJECTS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(OBJECTS) $(CFLAGS) -o $(BIN_DIR)/$(EXE)

$(OBJECTS): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.$(SRC_EXT)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(WFLAGS) -I$(INCLUDE_DIR) -c $< -o $@

clean:
	rm $(OBJECTS) $(BIN_DIR)/$(EXE) -v

run:
	./$(BIN_DIR)/$(EXE)
