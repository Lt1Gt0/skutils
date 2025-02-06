#File Directory things (might be overkill idk yet)
SRC_DIR := src
SRC_HEADER_DIR := $(SRC_DIR)/headers
SRC_INCLUDE := -I$(SRC_HEADER_DIR)

TEST_DIR := test 
TEST_HEADER_DIR := $(TEST_DIR)/headers
TEST_INCLUDES := -I$(TEST_DIR)/headers

OBJ_DIR := obj
TEST_OBJ_DIR := $(OBJ_DIR)/test
SRC_OBJ_DIR := $(OBJ_DIR)/src

LOG_DIR = logs

CC = g++
CCFLAGS = -g -Wall -Wextra --std=c++17

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

#Essential files and groups
OBJ = flag-parser-test 
SRCS = $(call rwildcard, $(SRC_DIR), *.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

all: $(OBJ) 
LIB_SRCS = $(call rwildcard, $(SRC_DIR), *.cpp)
LIB_OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(SRC_OBJ_DIR)/%.o, $(LIB_SRCS))
LIB_PREREQUISITES = $(LIB_SRCS) $(LIB_OBJS)

# TEST_SRCS = $(call rwildcard, $(TEST_DIR), *.cpp)
# TEST_OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(TEST_OBJ_DIR)/%.o, $(TEST_SRCS))
SETUP_DIRS = $(OBJ_DIR) $(SRC_OBJ_DIR) $(TEST_OBJ_DIR) $(LOG_DIR)

DIR_GUARD := @mkdir -p $(@D)

.PHONY: help
help:
	@echo 'For convenience'
	@echo
	@echo 'Available make targets:'
	@grep PHONY: Makefile | cut -d: -f2 | sed '1d;s/^/make/'

.PHONY: setup
setup:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(LOG_DIR)

.PHONY: all
all: clean obj
	@mkdir -p $(LOG_DIR)
	@mkdir -p $(@D)
	@echo ---- Generating $^ ---

.PHONY: lib
obj: $(OBJ)
	@echo ---- Generating $^ ---

$(LIB): $(OBJ)
	@ar rcs $(LIB) $(OBJ)

$(OBJ): $(OBJS)
	@echo ---- Linking $^ ----
	@mkdir -p $(@D)
	$(CC) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo ---- Compiling $^ ----
	@mkdir -p $(@D)
	$(CC) $(CCFLAGS) $(SRC_INCLUDE) -c $< -o $@

clean:
	rm $(OBJ)
	rm -rf $(OBJ_DIR)/
	rm -rf $(LOG_DIR)/
