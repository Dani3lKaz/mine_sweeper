#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"
#include "game.h"

int main(int argc, char **argv) {
    Field **board;
    Difficulty level;
    srand(time(NULL));
    level = choose_difficulty();
    if(level.c * level.r < level.mines || level.mines < 1) {
        fprintf(stderr, "Nieprawidlowe dane planszy. Sprobuj ponownie\n");
        return 1;
    }
    printf("r = %d, c = %d, mines = %d\n", level.r, level.c, level.mines);
    board = generate_board(level.r, level.c, level.mines);
    print_board(board, level.r, level.c);
    int result = read_fields(board, level.r, level.c);
    
    return 0;
}
