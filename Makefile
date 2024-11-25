# Compiler and flags
CXX = /usr/bin/g++
CXXFLAGS = -fdiagnostics-color=always -g -std=c++20

# Directories
SRC_DIR = src
INC_DIR = include
OUT_DIR = bin
OBJ_DIR = object

# Files
MAIN_CPP = main.cpp
SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES)) $(OBJ_DIR)/main.o
OUT_FILE = $(OUT_DIR)/main

# Targets
all: $(OBJ_DIR) $(OUT_FILE)

# Ensure the object directory exists
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Build the final executable
$(OUT_FILE): $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) -o $(OUT_FILE)

# Rule to compile source files into object files in object/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

# Rule to compile main.cpp into object/
$(OBJ_DIR)/main.o: $(MAIN_CPP)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) -c $< -o $@

# Clean up only build artifacts
clean:
	rm -rf $(OBJ_DIR) $(OUT_FILE)

.PHONY: all clean
