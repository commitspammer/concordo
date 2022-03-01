SRC_DIR = src
INCLUDE_DIR = include
BIN_DIR = bin
DATA_DIR = data

CXX ?= g++
CFLAGS = -std=c++11 -Wall -g
LFLAGS =
F =

SRC = $(wildcard $(SRC_DIR)/*.cpp)
OBJ = $(SRC:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%.o)
EXE = $(BIN_DIR)/concordo

install: setup $(EXE)

clean: setup
	echo -n ===CLEANING UP ' '
	rm -f $(BIN_DIR)/*.o $(EXE)
	echo OK

setup:
	echo -n ===SETTING UP ' '
	mkdir -p $(SRC_DIR) $(BIN_DIR) $(INCLUDE_DIR) $(DATA_DIR)
	echo OK

$(EXE): $(OBJ)
	echo -n ===LINKING $(EXE) ' '
	$(CXX) $^ -I $(INCLUDE_DIR) -o $@ $(LFLAGS)
	echo OK

$(OBJ): $(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	echo -n ===COMPILING $< ' '
	$(CXX) -c $< -I $(INCLUDE_DIR) -o $@ $(CFLAGS)
	echo OK

run:
ifeq ($(strip $(F)),)
	./$(EXE)
else
	./$(EXE) < $(F)
endif

test:
	for file in $(DATA_DIR)/* ; do echo ===TESTING $${file} ; ./$(EXE) < $${file} ; done

debug:
	echo SRC: $(SRC)
	echo OBJ: $(OBJ)
	echo EXE: $(EXE)

.PHONY: install setup clean single run test debug
.SILENT: install setup clean $(EXE) $(OBJ) single run test debug
