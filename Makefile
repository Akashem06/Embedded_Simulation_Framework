CPP = g++
C = gcc
CPPFLAGS = -Wall -Wextra -pthread
CFLAGS = -Wall -Wextra

SERVER_DIR = server
CLIENT_DIR = client
COMMON_DIR = common
DRIVERS_DIR = drivers

COMMON_SRC_DIR = $(COMMON_DIR)/src
COMMON_INC_DIR = $(COMMON_DIR)/inc

SERVER_APP_SRC_DIR = $(SERVER_DIR)/app/src
SERVER_APP_INC_DIR = $(SERVER_DIR)/app/inc
SERVER_UTILS_SRC_DIR = $(SERVER_DIR)/utils/src
SERVER_UTILS_INC_DIR = $(SERVER_DIR)/utils/inc

CLIENT_APP_SRC_DIR = $(CLIENT_DIR)/app/src
CLIENT_APP_INC_DIR = $(CLIENT_DIR)/app/inc
CLIENT_UTILS_SRC_DIR = $(CLIENT_DIR)/utils/src
CLIENT_UTILS_INC_DIR = $(CLIENT_DIR)/utils/inc

DRIVERS_SRC_DIR = $(DRIVERS_DIR)/src
DRIVERS_INC_DIR = $(DRIVERS_DIR)/inc

BUILD_DIR = build

COMMON_SRC = $(wildcard $(COMMON_SRC_DIR)/*.cpp)
COMMON_INC = $(wildcard $(COMMON_INC_DIR)/*.h)
COMMON_OBJS = $(patsubst $(COMMON_SRC_DIR)/%.cpp,$(BUILD_DIR)/common/%.o,$(COMMON_SRC))

SERVER_APP_SRC = $(wildcard $(SERVER_APP_SRC_DIR)/*.cpp)
SERVER_APP_INC = $(wildcard $(SERVER_APP_INC_DIR)/*.h)
SERVER_APP_OBJS = $(patsubst $(SERVER_APP_SRC_DIR)/%.cpp,$(BUILD_DIR)/server/app/%.o,$(SERVER_APP_SRC))

SERVER_UTILS_SRC = $(wildcard $(SERVER_UTILS_SRC_DIR)/*.cpp)
SERVER_UTILS_INC = $(wildcard $(SERVER_UTILS_SRC_DIR)/*.h)
SERVER_UTILS_OBJS = $(patsubst $(SERVER_UTILS_SRC_DIR)/%.cpp,$(BUILD_DIR)/server/utils/%.o,$(SERVER_UTILS_SRC))

CLIENT_APP_SRC = $(wildcard $(CLIENT_APP_SRC_DIR)/*.cpp)
CLIENT_INC_SRC = $(wildcard $(CLIENT_APP_INC_DIR)/*.h)
CLIENT_APP_OBJS = $(patsubst $(CLIENT_APP_SRC_DIR)/%.cpp,$(BUILD_DIR)/client/app/%.o,$(CLIENT_APP_SRC))

CLIENT_UTILS_SRC = $(wildcard $(CLIENT_UTILS_SRC_DIR)/*.cpp)
CLIENT_UTILS_INC = $(wildcard $(CLIENT_UTILS_INC_DIR)/*.h)
CLIENT_UTILS_OBJS = $(patsubst $(CLIENT_UTILS_SRC_DIR)/%.cpp,$(BUILD_DIR)/client/utils/%.o,$(CLIENT_UTILS_SRC))

DRIVERS_SRC = $(wildcard $(DRIVERS_SRC_DIR)/*.c)
DRIVERS_INC = $(wildcard $(DRIVERS_INC_DIR)/*.h)
DRIVERS_OBJS = $(patsubst $(DRIVERS_SRC_DIR)/%.c,$(BUILD_DIR)/drivers/%.o,$(DRIVERS_SRC))

SERVER_TARGET = tcp_server
CLIENT_TARGET = tcp_client

all: server client

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)/common
	mkdir -p $(BUILD_DIR)/server/app
	mkdir -p $(BUILD_DIR)/server/utils
	mkdir -p $(BUILD_DIR)/client/app
	mkdir -p $(BUILD_DIR)/client/utils
	mkdir -p $(BUILD_DIR)/drivers

server: $(BUILD_DIR)/$(SERVER_TARGET)
client: $(BUILD_DIR)/$(CLIENT_TARGET)

$(BUILD_DIR)/common/%.o: $(COMMON_SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CPP) $(CPPFLAGS) -I$(COMMON_INC_DIR) -I$(SERVER_APP_INC_DIR) -I$(SERVER_UTILS_INC_DIR) -I$(CLIENT_APP_INC_DIR) -I$(CLIENT_UTILS_INC_DIR) -c $< -o $@

$(BUILD_DIR)/server/app/%.o: $(SERVER_APP_SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CPP) $(CPPFLAGS) -I$(SERVER_APP_INC_DIR) -I$(SERVER_UTILS_INC_DIR) -I$(COMMON_INC_DIR) -c $< -o $@

$(BUILD_DIR)/server/utils/%.o: $(SERVER_UTILS_SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CPP) $(CPPFLAGS) -I$(SERVER_APP_INC_DIR) -I$(SERVER_UTILS_INC_DIR) -I$(COMMON_INC_DIR) -c $< -o $@

$(BUILD_DIR)/client/app/%.o: $(CLIENT_APP_SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CPP) $(CPPFLAGS) -I$(CLIENT_APP_INC_DIR) -I$(CLIENT_UTILS_INC_DIR) -I$(COMMON_INC_DIR) -I$(DRIVERS_INC_DIR) -c $< -o $@

$(BUILD_DIR)/client/utils/%.o: $(CLIENT_UTILS_SRC_DIR)/%.cpp | $(BUILD_DIR)
	$(CPP) $(CPPFLAGS) -I$(CLIENT_APP_INC_DIR) -I$(CLIENT_UTILS_INC_DIR) -I$(COMMON_INC_DIR) -c $< -o $@

$(BUILD_DIR)/drivers/%.o: $(DRIVERS_SRC_DIR)/%.c | $(BUILD_DIR)
	$(C) $(CFLAGS) -I$(DRIVERS_INC_DIR) -c $< -o $@

$(BUILD_DIR)/$(SERVER_TARGET): $(COMMON_OBJS) $(SERVER_APP_OBJS) $(SERVER_UTILS_OBJS)
	$(CPP) $(CPPFLAGS) $^ -o $@

$(BUILD_DIR)/$(CLIENT_TARGET): $(DRIVERS_OBJS) $(COMMON_OBJS) $(CLIENT_APP_OBJS) $(CLIENT_UTILS_OBJS)
	$(CPP) $(CPPFLAGS) $^ -o $@

clean:
	rm -rf $(BUILD_DIR)

format:
	clang-format -i -style=file $(COMMON_SRC) $(COMMON_INC) \
	$(SERVER_APP_SRC) $(SERVER_APP_INC) $(SERVER_UTILS_SRC) $(SERVER_UTILS_INC) \
	$(CLIENT_APP_SRC) $(CLIENT_APP_INC) $(CLIENT_UTILS_SRC) $(CLIENT_UTILS_INC) \
	$(DRIVERS_SRC) $(DRIVERS_INC)

.PHONY: all clean server client format
