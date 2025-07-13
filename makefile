CC = gcc
WARNINGS = -Wall -Wextra -Wsign-conversion -Wconversion
CFLAGS = $(WARNINGS) -I$(INCLUDE_DIR)

SRC_DIR = ./src
INCLUDE_DIR = ./include
BUILD_DIR = ./build

SOURCES = $(shell find $(SRC_DIR) -name "*.c")
OBJECTS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SOURCES))

PROJ = http_server

all: $(BUILD_DIR) $(BUILD_DIR)/$(PROJ)

$(BUILD_DIR):
	mkdir -p $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/$(PROJ): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $@ $(LFLAGS)

clean:
	rm -rf $(BUILD_DIR)