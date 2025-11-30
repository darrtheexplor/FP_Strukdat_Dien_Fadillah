# Compiler
CXX := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -Iinclude -MMD -MP

# SFML libraries
LIBS := -lsfml-graphics -lsfml-window -lsfml-system

# Source files
SRC := $(shell find src -name '*.cpp')

# Object files output
OBJ_DEBUG := $(SRC:src/%.cpp=build/debug/%.o)
OBJ_RELEASE := $(SRC:src/%.cpp=build/release/%.o)

# Binary output
BIN_DEBUG := bin/app-debug
BIN_RELEASE := bin/app

# Default target
all: release

# Debug build
debug: CXXFLAGS += -g -O0
debug: $(BIN_DEBUG)

$(BIN_DEBUG): $(OBJ_DEBUG)
	@mkdir -p $(dir $@)
	$(CXX) $(OBJ_DEBUG) -o $@ $(LIBS)

build/debug/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Release build
release: CXXFLAGS += -O2 -DNDEBUG
release: $(BIN_RELEASE)

$(BIN_RELEASE): $(OBJ_RELEASE)
	@mkdir -p $(dir $@)
	$(CXX) $(OBJ_RELEASE) -o $@ $(LIBS)

build/release/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean
clean:
	rm -rf build bin

# Include dependency files
-include $(OBJ_DEBUG:.o=.d)
-include $(OBJ_RELEASE:.o=.d)

.PHONY: all debug release clean
