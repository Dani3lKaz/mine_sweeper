#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "board.h"
#include "game.h"

Difficulty choose_difficulty() {
    int lvl;
    Difficulty level;
    printf("Prosze wybrac poziom trudnosci:\n 1 - Latwy\n2 - Sredni\n3 - Trudny\n4 - Wlasna plansza\n");
    scanf("%d", &lvl);
    if(lvl == 1) {
        level.r = 9;
        level.c = 9;
        level.mines = 10;
        level.multiplier = 1;
        return level;
    }else if(lvl == 2) {
        level.r = 16;
        level.c = 16;
        level.mines = 40;
        level.multiplier = 2;
        return level;
    }else if(lvl == 3) {
        level.r = 16;
        level.c = 30;
        level.mines = 99;
        level.multiplier = 3;
        return level;
    }else if(lvl == 4) {
        printf("Podaj liczbe wierszy: ");
        scanf("%d", &level.r);
        printf("Podaj liczbe kolumn: ");
        scanf("%d", &level.c);
        printf("Podaj liczbe min: ");
        scanf("%d", &level.mines);
        level.multiplier = 1;
        return level;
    }
}

Field **generate_board(int r, int c) {
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
    return board;
}

void generate_mines(Field **board, int r, int c, int mines, int start_x, int start_y) {
    int i;
    int j;
    int count = 0;
    while(count < mines) {
        int a = rand() % r;
        int b = rand() % c;
        if(board[a][b].isbomb != 1 && (a != start_x || b != start_y)) {
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
}

void print_board(Field **board, int r, int c, int points, int flags, int isfinished) {
    int i;
    int j;
    printf("    ");
    for(i = 0; i < c; i++) {
        printf("|%2d ", i + 1);
    }
    printf("|\n");
    for(i = 0; i < r; i++) {
        for(j = 0; j <= c; j++) {
            printf("+---");
        }
        printf("+\n");
        printf(" %2d ", i + 1);
        for(j = 0; j < c; j++) {
            if(board[i][j].isbomb == 1 && isfinished == 1){
                printf("|\e[0;31m * \e[0m");
            }else if(board[i][j].isread == 1 && isfinished == 0) {
                if(board[i][j].number == 0) {
                    printf("|   ");
                }else{
                    printf("| \e[%sm%d\e[0m ", 
                        board[i][j].number == 1 ? "0;34" : 
                        board[i][j].number == 2 ? "0;32" : 
                        board[i][j].number == 3 ? "0;31" :  
                        board[i][j].number == 4 ? "0;35" : 
                        board[i][j].number == 5 ? "0;33" :  
                        board[i][j].number == 6 ? "0;36" :  
                        board[i][j].number == 7 ? "0;30" :  
                        "0;37",
                        board[i][j].number);
                }
            }else if(board[i][j].isflag == 1) {
                printf("|\e[0;31m F \e[0m");
            }else if(board[i][j].isread == 0 && isfinished == 0) {
                printf("|###");
            }else{
                printf("|   ");
            }
        }
        printf("|\n");
    }
    for(j = 0; j <= c; j++) {
        printf("+---");
    }
    printf("+\n");
    printf("\nTwoj wynik: %d        Pozostale flagi: %d\n", points, flags);
}

Field **load_board(const char *filename, int *r, int *c, int *mines) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Nie można otworzyć pliku %s\n", filename);
        return NULL;
    }

    char ch;
    int temp_c = 0;

    while ((ch = getc(file)) != EOF) {
        if (ch == '*') {
            (*mines)++;
        } else if (ch >= '0' && ch <= '8') {
        } else if (ch == '\n') {
            if (*r == 0) {
                *c = temp_c;
            }
            (*r)++;
            temp_c = 0;
        } else if (ch == ' ') {
            continue;
        }else if (ch == 'r' || ch == 'f') {
            break;
        }else {
            fprintf(stderr, "Nieprawidłowy znak '%c' w pliku\n", ch);
            fclose(file);
            return NULL;
        }
        temp_c++;
    }

    Field **board = generate_board(*r, *c);
    rewind(file);

    int row = 0, col = 0;
    while ((ch = getc(file)) != EOF) {
        if (ch == '*') {
            board[row][col].isbomb = 1;
            col++;
        } else if (ch >= '0' && ch <= '8') {
            board[row][col].isbomb = 0;
            board[row][col].number = ch - '0';
            col++;
        } else if (ch == '\n') {
            row++;
            col = 0;
        } else if (ch == ' ') {
            continue;
        }else{
            break;
        }
    }

    print_board(board, *r, *c, 0, 0, 0);
    fclose(file);
    return board;
}

