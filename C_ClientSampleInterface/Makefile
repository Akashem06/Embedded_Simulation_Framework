CC = gcc
CXX = g++
CFLAGS = -Wall -Werror -g -O2
CXXFLAGS = -Wall -Werror -g -O2 -std=c++17

INCLUDES = -I./inc \
           -I../client/app/inc \
           -I../client/utils/inc \
           -I../common/inc

SRC_DIR = ./src
BUILD_DIR = ./build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

LIB_DIRS = -L../client/build/lib -L../common/build/lib -L../drivers/build/lib/
LIBS = -lclient -lcommon -ldrivers -lstdc++ -lpthread

C_SRCS = $(wildcard $(SRC_DIR)/*.c)
C_OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%_c.o, $(C_SRCS))

CXX_SRCS = $(wildcard $(SRC_DIR)/*.cc)
CXX_OBJS = $(patsubst $(SRC_DIR)/%.cc, $(OBJ_DIR)/%_cc.o, $(CXX_SRCS))

TARGET = $(BIN_DIR)/c_client_sample_interface

all: directories $(TARGET)

directories:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(BIN_DIR)

../client/build/lib/libclient.a:
	@echo "Building client library..."
	@$(MAKE) -C ../client

../common/build/lib/libcommon.a:
	@echo "Building common library..."
	@$(MAKE) -C ../common

../common/build/lib/libdrivers.a:
	@echo "Building drivers library..."
	@$(MAKE) -C ../drivers

$(OBJ_DIR)/%_c.o: $(SRC_DIR)/%.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%_cc.o: $(SRC_DIR)/%.cc
	@echo "Compiling C++ source $<..."
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(TARGET): $(C_OBJS) $(CXX_OBJS) ../client/build/lib/libclient.a ../common/build/lib/libcommon.a ../common/build/lib/libdrivers.a
	@echo "Linking $@..."
	@$(CXX) $(CXXFLAGS) -o $@ $(C_OBJS) $(CXX_OBJS) $(LIB_DIRS) $(LIBS) -Wl,-rpath=../client/build/lib:../common/build/lib:../drivers/build/lib
	@echo "Build complete: $@"

clean:
	@echo "Cleaning..."
	@rm -rf $(OBJ_DIR) $(BIN_DIR)

cleanall: clean
	@$(MAKE) -C ../client clean

run: all
	@echo "Running C Sample Interface..."
	@$(TARGET)

help:
	@echo "Available targets:"
	@echo "  all       - Build the C sample interface (default)"
	@echo "  clean     - Remove generated files"
	@echo "  cleanall  - Remove all generated files including dependencies"
	@echo "  run       - Build and run the C sample interface"
	@echo "  help      - Display this help message"

.PHONY: all directories clean cleanall run help
