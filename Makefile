CPP = g++
CPPFLAGS = -Wall -Wextra -pthread

SERVER_DIR = server
CLIENT_DIR = client
COMMON_DIR = common

COMMON_SRC_DIR = $(COMMON_DIR)/src
COMMON_INC_DIR = $(COMMON_DIR)/inc
SERVER_SRC_DIR = $(SERVER_DIR)/src
SERVER_INC_DIR = $(SERVER_DIR)/inc
CLIENT_SRC_DIR = $(CLIENT_DIR)/src
CLIENT_INC_DIR = $(CLIENT_DIR)/inc
BUILD_DIR = build

COMMON_SRC = $(wildcard $(COMMON_SRC_DIR)/*.cpp)
COMMON_OBJS = $(patsubst $(COMMON_SRC_DIR)/%.cpp,$(BUILD_DIR)/common/%.o,$(COMMON_SRC))

SERVER_SRC = $(wildcard $(SERVER_SRC_DIR)/*.cpp)
SERVER_OBJS = $(patsubst $(SERVER_SRC_DIR)/%.cpp,$(BUILD_DIR)/server/%.o,$(SERVER_SRC))

CLIENT_SRC = $(wildcard $(CLIENT_SRC_DIR)/*.cpp)
CLIENT_OBJS = $(patsubst $(CLIENT_SRC_DIR)/%.cpp,$(BUILD_DIR)/client/%.o,$(CLIENT_SRC))

SERVER_TARGET = tcp_server
CLIENT_TARGET = tcp_client

all: server client

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)/common
	mkdir -p $(BUILD_DIR)/server
	mkdir -p $(BUILD_DIR)/client

server: $(BUILD_DIR)/$(SERVER_TARGET)
client: $(BUILD_DIR)/$(CLIENT_TARGET)

$(BUILD_DIR)/common/%.o: $(COMMON_SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CPP) $(CPPFLAGS) -I$(COMMON_INC_DIR) -I$(SERVER_INC_DIR) -I$(CLIENT_INC_DIR) -c $< -o $@

$(BUILD_DIR)/server/%.o: $(SERVER_SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CPP) $(CPPFLAGS) -I$(SERVER_INC_DIR) -I$(COMMON_INC_DIR) -c $< -o $@

$(BUILD_DIR)/client/%.o: $(CLIENT_SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CPP) $(CPPFLAGS) -I$(CLIENT_INC_DIR) -I$(COMMON_INC_DIR) -c $< -o $@

$(BUILD_DIR)/$(SERVER_TARGET): $(COMMON_OBJS) $(SERVER_OBJS)
	$(CPP) $(CPPFLAGS) $^ -o $@

$(BUILD_DIR)/$(CLIENT_TARGET): $(COMMON_OBJS) $(CLIENT_OBJS)
	$(CPP) $(CPPFLAGS) $^ -o $@

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean server client
