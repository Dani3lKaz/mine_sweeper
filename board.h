#ifndef _BOARD_H_
#define _BOARD_H_

//Struktura komórki planszy
typedef struct {
    int isread; //informuje czy komórka jest odkryta (0 - nieodkryta; 1 - odkryta)
    int isbomb; //informuje czy w komórce znajduje się mina (0 - nie, 1- tak)
    int isflag; //informuje czy na komórce jest ustawiona flaga (0 - nie; 1 - tak)
    int number; //informuje o liczbie sąsiadujących komórek z minami
}Field;

//Struktura poziomu trudności
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
Field **load_board(const char *filename, int *r, int *c, int *mines);
void free_board(Field **board, int r);
void clear();

#endif

