TARGET = Minesweeper

CFLAGS = -Wall

ifeq ($(OS),Windows_NT)
    RM = del /f /q
    EXE = .exe
else
    RM = rm -f
    EXE =
endif

all: $(TARGET)

$(TARGET): main.o board.o game.o results.o
	gcc $(CFLAGS) main.o board.o game.o results.o -o $(TARGET)

main.o: main.c
	gcc $(CFLAGS) -c main.c

board.o: main.c
	gcc $(CFLAGS) -c board.c

game.o: main.c
	gcc $(CFLAGS) -c game.c

results.o: main.c
	gcc $(CFLAGS) -c results.c

clean:
	$(RM) main.o game.o board.o results.o $(TARGET)$(EXE)
