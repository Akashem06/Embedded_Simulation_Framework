PROJECT_NAME = SimulationFramework

CPP = g++
C = gcc
CPPFLAGS = -Wall -Wextra -pthread
CFLAGS = -Wall -Wextra

SIMULATION_DIR 			?= simulation
DRIVERS_DIR 			?= drivers
CAN_DIR 				?= can

ROOT_DIR 				:= $(shell pwd)
BUILD_DIR 				:= $(ROOT_DIR)/build/$(PROJECT_NAME)

SERVER_DIR 				:= server
CLIENT_DIR 				:= client
COMMON_DIR 				:= common

COMMON_SRC_DIR 			= $(COMMON_DIR)/src
COMMON_INC_DIR 			= $(COMMON_DIR)/inc

SERVER_APP_SRC_DIR 		= $(SERVER_DIR)/app/src
SERVER_APP_INC_DIR 		= $(SERVER_DIR)/app/inc
SERVER_UTILS_SRC_DIR 	= $(SERVER_DIR)/utils/src
SERVER_UTILS_INC_DIR 	= $(SERVER_DIR)/utils/inc

CLIENT_APP_SRC_DIR 		= $(CLIENT_DIR)/app/src
CLIENT_APP_INC_DIR 		= $(CLIENT_DIR)/app/inc
CLIENT_UTILS_SRC_DIR 	= $(CLIENT_DIR)/utils/src
CLIENT_UTILS_INC_DIR 	= $(CLIENT_DIR)/utils/inc

DRIVERS_SRC_DIR 		= $(DRIVERS_DIR)/src
DRIVERS_INC_DIR 		= $(DRIVERS_DIR)/inc

CAN_SRC_DIR 			= $(CAN_DIR)/src
CAN_INC_DIR 			= $(CAN_DIR)/inc

# Source files
COMMON_SRCS := $(wildcard $(COMMON_DIR)/src/*.cpp)
SERVER_APP_SRCS := $(wildcard $(SERVER_DIR)/app/src/*.cpp)
SERVER_UTILS_SRCS := $(wildcard $(SERVER_DIR)/utils/src/*.cpp)
CLIENT_APP_SRCS := $(wildcard $(CLIENT_DIR)/app/src/*.cpp)
CLIENT_UTILS_SRCS := $(wildcard $(CLIENT_DIR)/utils/src/*.cpp)
DRIVERS_SRCS := $(wildcard $(DRIVERS_DIR)/src/*.c)
CAN_SRCS := $(wildcard $(CAN_DIR)/src/*.c)

# Object files
COMMON_OBJS := $(patsubst $(COMMON_DIR)/src/%.cpp,$(BUILD_DIR)/common/%.o,$(COMMON_SRCS))
SERVER_APP_OBJS := $(patsubst $(SERVER_DIR)/app/src/%.cpp,$(BUILD_DIR)/server/app/%.o,$(SERVER_APP_SRCS))
SERVER_UTILS_OBJS := $(patsubst $(SERVER_DIR)/utils/src/%.cpp,$(BUILD_DIR)/server/utils/%.o,$(SERVER_UTILS_SRCS))
CLIENT_APP_OBJS := $(patsubst $(CLIENT_DIR)/app/src/%.cpp,$(BUILD_DIR)/client/app/%.o,$(CLIENT_APP_SRCS))
CLIENT_UTILS_OBJS := $(patsubst $(CLIENT_DIR)/utils/src/%.cpp,$(BUILD_DIR)/client/utils/%.o,$(CLIENT_UTILS_SRCS))
DRIVERS_OBJS := $(patsubst $(DRIVERS_DIR)/src/%.c,$(BUILD_DIR)/drivers/%.o,$(DRIVERS_SRCS))
CAN_OBJS := $(patsubst $(CAN_DIR)/src/%.c,$(BUILD_DIR)/can/%.o,$(CAN_SRCS))

SERVER_TARGET = sim_server
CLIENT_TARGET = sim_client

.PHONY: all clean server client format help

all: server client

help:
	@echo "Available targets:"
	@echo "  all      		 	- Build both server and client (default)"
	@echo "  server   		 	- Build only the server"
	@echo "  client   		 	- Build only the client"
	@echo "  clean    		 	- Remove build directory"
	@echo "  format   		 	- Format source files using clang-format"
	@echo ""
	@echo "Configuration:"
	@echo "  BUILD_TYPE      	- Debug or Release (default: Debug)"
	@echo "  SIMULATION_DIR  	- Path to simulation directory"
	@echo "  DRIVERS_DIR     	- Path to drivers directory"
	
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)/common
	mkdir -p $(BUILD_DIR)/server/app
	mkdir -p $(BUILD_DIR)/server/utils
	mkdir -p $(BUILD_DIR)/client/app
	mkdir -p $(BUILD_DIR)/client/utils
	mkdir -p $(BUILD_DIR)/drivers
	mkdir -p $(BUILD_DIR)/can

autogen_sim_server_files:
	@echo "Running autogen scripts..."
	@python3 -m autogen system_can -o $(SERVER_APP_INC_DIR)
	@python3 -m autogen simulation_app -o $(SERVER_DIR)/app

server: autogen_sim_server_files $(BUILD_DIR)/$(SERVER_TARGET)

client: $(BUILD_DIR)/$(CLIENT_TARGET)

$(BUILD_DIR)/common/%.o: $(COMMON_SRC_DIR)/%.cpp | $(BUILD_DIR)
	@echo "Compiling $<"
	$(CPP) $(CPPFLAGS) -I$(COMMON_INC_DIR) -I$(SERVER_APP_INC_DIR) -I$(SERVER_UTILS_INC_DIR) -I$(CLIENT_APP_INC_DIR) -I$(CLIENT_UTILS_INC_DIR) -c $< -o $@

$(BUILD_DIR)/server/app/%.o: $(SERVER_APP_SRC_DIR)/%.cpp | $(BUILD_DIR)
	@echo "Compiling $<"
	$(CPP) $(CPPFLAGS) -I$(SERVER_APP_INC_DIR) -I$(SERVER_UTILS_INC_DIR) -I$(COMMON_INC_DIR) -c $< -o $@

$(BUILD_DIR)/server/utils/%.o: $(SERVER_UTILS_SRC_DIR)/%.cpp | $(BUILD_DIR)
	@echo "Compiling $<"
	$(CPP) $(CPPFLAGS) -I$(SERVER_APP_INC_DIR) -I$(SERVER_UTILS_INC_DIR) -I$(COMMON_INC_DIR) -c $< -o $@

$(BUILD_DIR)/client/app/%.o: $(CLIENT_APP_SRC_DIR)/%.cpp | $(BUILD_DIR)
	@echo "Compiling $<"
	$(CPP) $(CPPFLAGS) -I$(CLIENT_APP_INC_DIR) -I$(CLIENT_UTILS_INC_DIR) -I$(COMMON_INC_DIR) -I$(DRIVERS_INC_DIR) -I$(CAN_INC_DIR) -c $< -o $@

$(BUILD_DIR)/client/utils/%.o: $(CLIENT_UTILS_SRC_DIR)/%.cpp | $(BUILD_DIR)
	@echo "Compiling $<"
	$(CPP) $(CPPFLAGS) -I$(CLIENT_APP_INC_DIR) -I$(CLIENT_UTILS_INC_DIR) -I$(COMMON_INC_DIR) -c $< -o $@

$(BUILD_DIR)/drivers/%.o: $(DRIVERS_SRC_DIR)/%.c | $(BUILD_DIR)
	@echo "Compiling $<"
	$(C) $(CFLAGS) -I$(DRIVERS_INC_DIR) -c $< -o $@

$(BUILD_DIR)/can/%.o: $(CAN_SRC_DIR)/%.c | $(BUILD_DIR)
	@echo "Compiling $<"
	$(C) $(CFLAGS) -I$(CAN_INC_DIR) -I$(DRIVERS_INC_DIR) -c $< -o $@

$(BUILD_DIR)/$(SERVER_TARGET): $(COMMON_OBJS) $(SERVER_APP_OBJS) $(SERVER_UTILS_OBJS)
	@echo "Linking..."
	$(CPP) $(CPPFLAGS) $^ -o $@

$(BUILD_DIR)/$(CLIENT_TARGET): $(DRIVERS_OBJS) $(CAN_OBJS) $(COMMON_OBJS) $(CLIENT_APP_OBJS) $(CLIENT_UTILS_OBJS)
	@echo "Linking..."
	$(CPP) $(CPPFLAGS) $^ -o $@

init_vcan:
	@sudo modprobe vcan
	@sudo modprobe can_bcm
	@sudo modprobe can_raw
	@sudo ip link add dev vcan0 type vcan
	@sudo ip link set up vcan0

format:
	@echo "Formatting source files..."
	@find . -type f \( -name "*.cpp" -o -name "*.h" -o -name "*.c" \) -exec clang-format -i -style=file {} +

clean:
	@echo "Cleaning build directory..."
	@rm -rf $(BUILD_DIR)

.PHONY: all clean server client format init_vcan
