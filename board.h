#ifndef _BOARD_H_
#define _BOARD_H_

typedef struct {
    int isread;
    int isbomb;
    int isflag;
    int number;
}Field;

typedef struct {
    int r;
    int c;
    int mines;
    int multiplier;
} Difficulty;

Difficulty choose_difficulty();
Field **generate_board(int r, int c);
void generate_mines(Field **board, int r, int c, int mines, int start_x, int start_y);
void print_board(Field **board, int r, int c, int points, int flags, int isfinished);

#endif

