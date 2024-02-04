UNAME   := $(shell uname)
CC       = gcc
CFLAGS   = -Wall -Wextra -Werror -Iinclude
LDFLAGS  = -lraylib -O1

ifeq ($(UNAME), Linux)
	LDFLAGS += -lGL -lm -lpthread -ldl -lrt -lX11
else ifeq ($(OS), Windows_NT)
	LDFLAGS += -lopengl32 -lgdi32 -lwinmm
endif

ifeq ($(BUILD_TYPE), RELEASE)
CFLAGS += -DRELEASE_BUILD
endif

SRC_DIR   = src
DATA_DIR  = data
BUILD_DIR = build/snake-game
BIN_DIR   = build/bin
TARGET    = $(BIN_DIR)/snakegame

SOURCE_DIRS   = $(shell find $(SRC_DIR) -type d)
SOURCE_FILES  = $(foreach dir, $(SOURCE_DIRS), $(wildcard $(dir)/*.c))
OBJECTS       = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SOURCE_FILES))
BUILD_SUBDIRS = $(patsubst $(SRC_DIR)/%, $(BUILD_DIR)/%, $(SOURCE_DIRS))


$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR) $(BUILD_SUBDIRS)
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

$(BUILD_SUBDIRS):
	@mkdir -p $@

DATA_DIR := data
$(shell mkdir -p $(DATA_DIR))


clean:
	@rm -rf build
	@echo "Build cleaned"

run: $(TARGET)
	./$(TARGET)


.PHONY: clean
.PHONY: run

