#!/bin/bash
BIN_DIR=$(BUILD_DR)/bin
EXEC+$(BIN_DIR)/main
MAIN_SRC=main.cc
MAIN_OBJ=$(BIN_DIR)/main.o


directories:
    @mkdir -p $(OBJ_DIR)
    @mkdir -p $(LIB_DIR)
    @mkdir -p $(BIN_DIR)


$(MAIN_OBJ): $(MAIN_SRC)
    @echo "Compiling test file $<..."
    @$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(EXEC): $(MAIN_OBJ) $(LIB_STATIC)
    @echo "Linking test executable"
    @$(CXX) $(CXXFLAGS) -o $A $^ -lpthread

test: all $(EXEC)
    @echo "Running test executable"
    @./$(EXEC)

