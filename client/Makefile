CC = gcc
CXX = g++
CFLAGS = -Wall -Werror -g -O2 -fPIC
CXXFLAGS = -Wall -g -O2 -std=c++17 -fPIC

# Include directories
INCLUDES = -I./inc \
           -I./app/inc \
           -I./utils/inc \
           -I../common/inc \
		   -I../drivers/inc

# Source directories
SRC_DIR = ./src
APP_SRC_DIR = ./app/src
UTILS_SRC_DIR = ./utils/src
BUILD_DIR = ./build
OBJ_DIR = $(BUILD_DIR)/obj
LIB_DIR = $(BUILD_DIR)/lib

# Source files
CXX_SRCS = $(wildcard $(SRC_DIR)/*.cc) $(wildcard $(SRC_DIR)/*.cpp)
APP_SRCS = $(wildcard $(APP_SRC_DIR)/*.cc) $(wildcard $(APP_SRC_DIR)/*.cpp)
UTILS_SRCS = $(wildcard $(UTILS_SRC_DIR)/*.cc) $(wildcard $(UTILS_SRC_DIR)/*.cpp)

# Object files
CXX_OBJS = $(patsubst $(SRC_DIR)/%.cc, $(OBJ_DIR)/%.o, $(filter %.cc, $(CXX_SRCS)))
CXX_OBJS += $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(filter %.cpp, $(CXX_SRCS)))
APP_OBJS = $(patsubst $(APP_SRC_DIR)/%.cc, $(OBJ_DIR)/app_%.o, $(filter %.cc, $(APP_SRCS)))
APP_OBJS += $(patsubst $(APP_SRC_DIR)/%.cpp, $(OBJ_DIR)/app_%.o, $(filter %.cpp, $(APP_SRCS)))
UTILS_OBJS = $(patsubst $(UTILS_SRC_DIR)/%.cc, $(OBJ_DIR)/utils_%.o, $(filter %.cc, $(UTILS_SRCS)))
UTILS_OBJS += $(patsubst $(UTILS_SRC_DIR)/%.cpp, $(OBJ_DIR)/utils_%.o, $(filter %.cpp, $(UTILS_SRCS)))

# All object files
ALL_OBJS = $(CXX_OBJS) $(APP_OBJS) $(UTILS_OBJS)

# Library target
LIB_STATIC = $(LIB_DIR)/libclient.a
LIB_SHARED = $(LIB_DIR)/libclient.so

all: directories $(LIB_STATIC) $(LIB_SHARED)

# Create necessary directories
directories:
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(LIB_DIR)

# Compile C++ source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cc
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Compile app source files
$(OBJ_DIR)/app_%.o: $(APP_SRC_DIR)/%.cc
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/app_%.o: $(APP_SRC_DIR)/%.cpp
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Compile utils source files
$(OBJ_DIR)/utils_%.o: $(UTILS_SRC_DIR)/%.cc
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR)/utils_%.o: $(UTILS_SRC_DIR)/%.cpp
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(LIB_STATIC): $(ALL_OBJS)
	@echo "Creating static library $@..."
	@ar rcs $@ $(ALL_OBJS)

$(LIB_SHARED): $(ALL_OBJS)
	@echo "Creating shared library $@..."
	@$(CXX) -shared -o $@ $(ALL_OBJS)

clean:
	@echo "Cleaning..."
	@rm -rf $(OBJ_DIR) $(LIB_DIR)

help:
	@echo "Available targets:"
	@echo "  all       - Build both static and shared libraries (default)"
	@echo "  clean     - Remove generated files"
	@echo "  help      - Display this help message"

.PHONY: all directories clean help