#File Directory things (might be overkill idk yet)
SOURCE_DIR = src/
SOURCE_HEADER_DIR = $(SOURCE_DIR)/headers

TEST_DIR = test/
TEST_HEADER_DIR = $(TEST_DIR)/headers

OBJ_DIR = obj
TEST_OBJ_DIR = $(OBJ_DIR)/test
SOURCE_OBJ_DIR = $(OBJ_DIR)/src

LOG_DIR = logs

CC = g++
CCFLAGS = -c

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

LIB_SOURCES = $(call rwildcard, $(SOURCE_DIR), *.cpp)
LIB_OBJS = $(patsubst $(SOURCE_DIR)/%.cpp, $(SOURCE_OBJ_DIR)/%.o, $(LIB_SOURCES))
LIB_PREREQUISITES = $(LIB_SOURCES) $(LIB_OBJS)

TEST_SOURCES = $(call rwildcard, $(TEST_DIR), *.cpp)
TEST_OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(TEST_OBJ_DIR)/%.o, $(TEST_SOURCES))

SETUP_DIRS = $(OBJ_DIR) $(SOURCE_OBJ_DIR) $(TEST_OBJ_DIR) $(LOG_DIR)

DIR_GUARD := @mkdir -p $(@D)

.PHONY: help
help:
	@echo 'For convenience'
	@echo
	@echo 'Available make targets:'
	@grep PHONY: Makefile | cut -d: -f2 | sed '1d;s/^/make/'

.PHONY: setup
setup:
	$(foreach dir, $(SETUP_DIRS), $(shell mkdir $(dir)))

.PHONY: clean
clean:
	$(foreach dir, $(SETUP_DIRS), $(shell rm $(dir) -r))

.PHONY: all
all: $(LIB)
	@mkdir -p $(LOG_DIR)
	@mkdir -p $(@D)
	@echo ---- Generating $^ ---


$(LIB): $(OBJ)
	@ar rcs $(LIB) $(OBJ)

$(OBJ): $(OBJS)
	# @mkdir -p $(@D)
	# $(CC) $(CCFLAGS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo ---- Compiling $^ ----
	@mkdir -p $(@D)
	$(CC) $(CCFLAGS) $(INCLUDE) $< -o $@
