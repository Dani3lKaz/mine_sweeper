#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"


Difficulty choose_difficulty() {
    int lvl;
    Difficulty level;
    printf("Prosze wybrac poziom trudnosci:\n 1 - Latwy\n2 - Sredni\n3 - Trudny\n4 - Wlasna plansza\n");
    scanf("%d", &lvl);
    if(lvl == 1) {
        level.r = 9;
        level.c = 9;
        level.mines = 10;
        return level;
    }else if(lvl == 2) {
        level.r = 16;
        level.c = 16;
        level.mines = 40;
        return level;
    }else if(lvl == 3) {
        level.r = 16;
        level.c = 30;
        level.mines = 99;
        return level;
    }else if(lvl == 4) {
        printf("Podaj liczbe wierszy: ");
        scanf("%d", &level.r);
        printf("Podaj liczbe kolumn: ");
        scanf("%d", &level.c);
        printf("Podaj liczbe min: ");
        scanf("%d", &level.mines);
        return level;
    }
}

Field **generate_board(int r, int c, int mines) {
    Field **board;
    board = malloc(r * sizeof(Field*));
    int i;
    int j;
    for(i = 0; i < r; i++) {
        board[i] = malloc(c * sizeof(Field));
    }
    for(i = 0; i < r; i++) {
        for(j = 0; j < c; j++) {
            board[i][j].isread = 0;
            board[i][j].isflag = 0;
            board[i][j].number = 0;
        }
    }
    int count = 0;
    while(count < mines) {
        int a = rand() % r;
        int b = rand() % c;
        if(board[a][b].isbomb != 1) {
            board[a][b].isbomb = 1;
            count++;
        }
    }
    for(i = 0; i < r; i++) {
        for(j = 0; j < c; j++) {
            if(board[i][j].isbomb != 1) {
                if(i-1 >= 0 && j-1 >= 0 && board[i-1][j-1].isbomb == 1) {
                    board[i][j].number++;
                }
                if(j-1 >= 0 && board[i][j-1].isbomb == 1) {
                    board[i][j].number++;
                }
                if(i+1 < r && j-1 >= 0 && board[i+1][j-1].isbomb == 1) {
                    board[i][j].number++;
                }
                if(i+1 < r && board[i+1][j].isbomb == 1) {
                    board[i][j].number++;
                }
                if(i+1 < r && j+1 < c && board[i+1][j+1].isbomb == 1) {
                    board[i][j].number++;
                }
                if(j+1 < c && board[i][j+1].isbomb == 1) {
                    board[i][j].number++;
                }
                if(i-1 >= 0 && j+1 < c && board[i-1][j+1].isbomb == 1) {
                    board[i][j].number++;
                }
                if(i-1 >= 0 && board[i-1][j].isbomb == 1) {
                    board[i][j].number++;
                }
            }
        }
    }
    return board;
}

void print_board(Field **board, int r, int c) {
    int i;
    int j;
    for(i = 0; i < r; i++) {
        for(j = 0; j < c; j++) {
            printf("+---");
        }
        printf("+\n");
        for(j = 0; j < c; j++) {
            if(board[i][j].isflag == 1) {
                printf("|\e[0;31m F \e[0m");
            }else if(board[i][j].isread == 1) {
                printf("| %d ", board[i][j].number);
            }else if(board[i][j].isread == 0) {
                printf("|   ");
            }
        }
        printf("|\n");
    }
    for(j = 0; j < c; j++) {
        printf("+---");
    }
    printf("+\n");
}