##
## EPITECH PROJECT, 2023
## B-YEP-400-STG-4-1-zappy-basile.trebus-hamann
## File description:
## Makefile
##

# Compiler and flags
CXX := g++
CXXFLAGS := -std=c++20 -Wall -Wextra -pedantic -ldl -lpthread -I./include -lraylib

# Directories
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := ./

NAME	=	zappy_gui

# Source files
SRCS := $(shell find $(SRC_DIR) -name "*.cpp")
OBJS := $(patsubst $(SRC_DIR)/%,$(OBJ_DIR)/%,$(SRCS:.cpp=.o))

# Include directories
INC_DIRS := $(shell find $(SRC_DIR) -type d)
INC_FLAGS := $(addprefix -I,$(INC_DIRS))

# Targets
TARGET := $(BIN_DIR)/$(NAME)

# Rules
all: $(TARGET)

$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	@$(CXX)  $^ $(CXXFLAGS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	@$(CXX)  $(INC_FLAGS) -c $< $(CXXFLAGS) -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(TARGET)

re: clean all

.PHONY: all clean
