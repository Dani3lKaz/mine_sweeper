#ifndef _GAME_H_
#define _GAME_H_
#include "board.h"

int are_all_read(Field **board, int r, int c);
void read_neighbors(Field **board, int r, int c, int x, int y);
int read_fields(Field **board, int r, int c);

#endif