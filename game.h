#ifndef _GAME_H_
#define _GAME_H_
#include "board.h"

int are_all_read(Field **board, int r, int c);
void read_fields(Field **board, int r, int c, int x, int y, int mode, int *points);
int execute_commands(Field **board, int r, int c, int mines, int *points, int multiplier);
void execute_commands_from_file(const char *filename, Field **board, int r, int c, int *points, int flags);

#endif