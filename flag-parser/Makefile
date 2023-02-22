#File Directory things (might be overkill idk yet)
INCLUDE = -I$(SRC_DIR)/headers
SRC_DIR = src
OBJ_DIR = obj
LOG_DIR = logs

#Compiler and linker things
CC = g++
CCFLAGS = -c

rwildcard=$(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))

#Essential files and groups
OBJ = libflagparse.o
LIB = libflagparse.a

SRCS = $(call rwildcard, $(SRC_DIR), *.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SRCS))

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

clean:
	rm $(OBJ)
	rm -rf $(OBJ_DIR)/
	rm -rf $(LOG_DIR)/
