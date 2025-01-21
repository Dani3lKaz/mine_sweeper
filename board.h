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
} Difficulty;

Difficulty choose_difficulty();
Field **generate_board(int r, int c, int mines);
void print_board(Field **board, int r, int c);

#endif

