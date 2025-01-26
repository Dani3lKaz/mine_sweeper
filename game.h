#ifndef _GAME_H_
#define _GAME_H_
#include "board.h"

int are_all_read(Field **board, int r, int c);
void read_fields(Field **board, int r, int c, int x, int y, int mode, int *points);
int game(Field **board, int r, int c, int mines, int *points, int multiplier);

#endif