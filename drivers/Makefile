CC = gcc
CFLAGS = -Wall -g -O2 -fPIC

# Include directories
INCLUDES = -I./inc \

# Source directories
SRC_DIR = ./src
BUILD_DIR = ./build
OBJ_DIR = $(BUILD_DIR)/obj
LIB_DIR = $(BUILD_DIR)/lib

# Source files
C_SRCS = $(wildcard $(SRC_DIR)/*.c)

# Object files
C_OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(filter %.c, $(C_SRCS)))

# All object files
ALL_OBJS = $(C_OBJS)

# Library target
LIB_STATIC = $(LIB_DIR)/libdrivers.a
LIB_SHARED = $(LIB_DIR)/libdrivers.so

all: directories $(LIB_STATIC) $(LIB_SHARED)

# Create necessary directories
directories:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(LIB_DIR)

# Compile C source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIB_STATIC): $(ALL_OBJS)
	@echo "Creating static library $@..."
	@ar rcs $@ $(ALL_OBJS)

$(LIB_SHARED): $(ALL_OBJS)
	@echo "Creating shared library $@..."
	@$(CC) -shared -o $@ $(ALL_OBJS)

clean:
	@echo "Cleaning..."
	@rm -rf $(OBJ_DIR) $(LIB_DIR)

help:
	@echo "Available targets:"
	@echo "  all       - Build both static and shared libraries (default)"
	@echo "  clean     - Remove generated files"
	@echo "  help      - Display this help message"

.PHONY: all directories clean help