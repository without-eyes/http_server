CC = gcc
WARNINGS = -Wall -Wextra -Wsign-conversion -Wconversion
CFLAGS = $(WARNINGS)

SERVER = server
CLIENT = http_client

SRC_DIR = ./src
BUILD_DIR = ./build

SERVER_SRC = $(shell find $(SRC_DIR)/$(SERVER) -name "*.c")
CLIENT_SRC = $(SRC_DIR)/$(CLIENT).c

.PHONY: server client clean
all: server client
server: $(BUILD_DIR) $(BUILD_DIR)/$(SERVER)
client: $(BUILD_DIR) $(BUILD_DIR)/$(CLIENT)

$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/$(SERVER): $(SERVER_SRC)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/$(CLIENT): $(CLIENT_SRC)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -rf $(BUILD_DIR)