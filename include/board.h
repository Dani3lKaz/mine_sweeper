#ifndef _BOARD_H_
#define _BOARD_H_
#include <stdbool.h>

typedef struct {
    bool isread; 
    bool isbomb; 
    bool isflag; 
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
void print_board(Field **board, int r, int c, int points, int flags, bool isfinished);
Field **load_board(const char *filename, int *r, int *c, int *mines);
void free_board(Field **board, int r);

#endif

