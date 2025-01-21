#include <stdio.h>
#include <windows.h>
#include "board.h"

int are_all_read(Field **board, int r, int c) {
    int i;
    int j;
    for(i = 0; i < r; i++) {
        for(j = 0; j < c; j++) {
            if(board[i][j].isbomb == 0 && board[i][j].isread == 0) {
                return 0;
            } 
        }
    }
    return 1;
}

void read_neighbors(Field **board, int r, int c, int x, int y) {
    if(x < 0 || x >= r || y < 0 || y >= c) {
        return;
    }

    if(board[x][y].isread == 1) {
        return;
    }

    board[x][y].isread = 1;

    if (board[x][y].number == 0) {
        read_neighbors(board, r, c, x - 1, y - 1);  
        read_neighbors(board, r, c, x - 1, y);      
        read_neighbors(board, r, c, x - 1, y + 1);  
        read_neighbors(board, r, c, x, y - 1);      
        read_neighbors(board, r, c, x, y + 1);   
        read_neighbors(board, r, c, x + 1, y - 1); 
        read_neighbors(board, r, c, x + 1, y);     
        read_neighbors(board, r, c, x + 1, y + 1);  
    }
}

int read_fields(Field **board, int r, int c) {
    char com;
    int x;
    int y;
    while(are_all_read(board, r, c) == 0) {
        scanf(" %c %d %d", &com, &x, &y);
        if(x-1 >= 0 && y-1 >= 0) {
            if(com == 'f') {
                if(board[x-1][y-1].isflag == 0) {
                    board[x-1][y-1].isflag = 1;
                }else{
                    board[x-1][y-1].isflag = 0;
                }
            }else if(com == 'r') {
                if(board[x-1][y-1].isflag == 0 && board[x-1][y-1].isbomb == 1) {
                    printf("Porazka! Trafiles na mine!\n");
                    return 0;
                }else if(board[x-1][y-1].isread == 0 && board[x-1][y-1].isflag == 0) {
                    board[x-1][y-1].isread = 1;
                    if(board[x-1][y-1].number == 0) {
                        read_neighbors(board, r, c, x-1, y-1);
                    }
                }
            }else{
                printf("Niepoprawna komenda! Dopuszczalne sa: f <x> <y> lub r <x> <y>\n");
            }
        }
        system("cls");
        print_board(board, r, c);
    }
    printf("Wygrana! Znalazles wszystkie miny\n");
    return 1;
}