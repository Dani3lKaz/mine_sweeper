TARGET = Minesweeper
TEST_TARGET = test

CC = gcc
CFLAGS = -Wall -Wextra -g -Iinclude

SRC_DIR = src
TEST_DIR = tests
BUILD_DIR = build

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TEST_TARGET): $(BUILD_DIR)/test.o build/board.o build/game.o build/results.o
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/test.o: $(TEST_DIR)/test.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) $(TARGET) $(TEST_TARGET)

.PHONY: all clean
