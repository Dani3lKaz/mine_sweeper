# Nazwa programu
TARGET = Minesweeper

# Kompilator i flagi
CC = gcc
CFLAGS = -Wall -Iinclude

# Katalogi
SRC_DIR = src
BUILD_DIR = build

# Pliki źródłowe i obiektowe
SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))

# Domyślny cel
all: $(TARGET)

# Linkowanie
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

# Kompilacja plików .c do .o (pattern rule)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Tworzenie katalogu build (jeśli nie istnieje)
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Czyszczenie
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean