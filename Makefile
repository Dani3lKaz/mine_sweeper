TARGET = Minesweeper

CFLAGS = -Wall



all: $(TARGET)

$(TARGET): main.0 board.o game.o results.o
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
	rm -f main.c board.c game.c results.c $(TARGET)
