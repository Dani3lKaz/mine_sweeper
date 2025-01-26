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

void read_fields(Field **board, int r, int c, int x, int y, int mode, int *points) {
    if(x < 0 || x >= r || y < 0 || y >= c) {
        return;
    }

    if(board[x][y].isread == 1 || board[x][y].isbomb == 1){
        return;
    }

    board[x][y].isread = 1;
    (*points)++;


    if (board[x][y].number == 0 || mode == 0) {
        read_fields(board, r, c, x - 1, y - 1, 1, points);  
        read_fields(board, r, c, x - 1, y, 1, points);      
        read_fields(board, r, c, x - 1, y + 1, 1, points);  
        read_fields(board, r, c, x, y - 1, 1, points);      
        read_fields(board, r, c, x, y + 1, 1, points);   
        read_fields(board, r, c, x + 1, y - 1, 1, points); 
        read_fields(board, r, c, x + 1, y, 1, points);     
        read_fields(board, r, c, x + 1, y + 1, 1, points);  
    }
}

int execute_commands(Field **board, int r, int c, int mines, int *points, int multiplier) {
    char com;
    int x;
    int y;
    int flags = mines;
    system("cls");
    print_board(board, r, c, *points, flags, 0);
    while(are_all_read(board, r, c) == 0) {
        scanf(" %c %d %d", &com, &x, &y);
        if(x-1 >= 0 && y-1 >= 0 && x <= r && y <= c) {
            if(com == 'f') {
                if(board[x-1][y-1].isflag == 0 && board[x-1][y-1].isread == 0 && flags > 0) {
                    board[x-1][y-1].isflag = 1;
                    flags--;
                }else if(board[x-1][y-1].isflag == 1){
                    board[x-1][y-1].isflag = 0;
                    flags++;
                }
            }else if(com == 'r') {
                if(*points == 0){
                    generate_mines(board, r, c, mines, x-1, y-1);
                    read_fields(board, r, c, x-1, y-1, 0, points);
                }else{
                    if(board[x-1][y-1].isflag == 0 && board[x-1][y-1].isbomb == 1) {
                        print_board(board, r, c, *points * multiplier, flags, 1);
                        return 0;
                    }else if(board[x-1][y-1].isread == 0 && board[x-1][y-1].isflag == 0) {
                        read_fields(board, r, c, x-1, y-1, 1, points);
                    }
                }
            }else{
                printf("Niepoprawna komenda! Dopuszczalne sa: f <x> <y> lub r <x> <y>\n");
                Sleep(2000);
            }
        }else{
            printf("Wspolrzedne poza plansza!\n");
            Sleep(2000);
        }
        system("cls");
        print_board(board, r, c, *points * multiplier, flags, 0);
    }
    print_board(board, r, c, *points * multiplier, flags, 1);
    return 1;
}

void execute_commands_from_file(const char *filename, Field **board, int r, int c, int *points, int flags) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Nie udalo sie otworzyc pliku z komendami.\n");
        return;
    }

    char com;
    int x;
    int y;

    char ch;
    while ((ch = getc(file)) != EOF) {
        if (ch == 'r' || ch == 'f') {
            break;
        }
    }

    fseek(file, -1, SEEK_CUR);

    while (fscanf(file, " %c %d %d", &com, &x, &y) == 3) {
        Sleep(1000);
        printf("Odczytana komenda %c %d %d\n", com, x, y);
        if(x-1 >= 0 && y-1 >= 0 && x <= r && y <= c) {
            if(com == 'f') {
                if(board[x-1][y-1].isflag == 0 && board[x-1][y-1].isread == 0 && flags > 0) {
                    board[x-1][y-1].isflag = 1;
                    flags--;
                }else if(board[x-1][y-1].isflag == 1){
                    board[x-1][y-1].isflag = 0;
                    flags++;
                }
            }else if(com == 'r') {
                if(board[x-1][y-1].isflag == 0 && board[x-1][y-1].isbomb == 1) {
                    printf("Porazka! Trafiono na mine!\n");
                    system("cls");
                    print_board(board, r, c, *points, flags, 1);
                    return;
                }else if(board[x-1][y-1].isread == 0 && board[x-1][y-1].isflag == 0) {
                    read_fields(board, r, c, x-1, y-1, 1, points);
                }
            }else{
                printf("Niepoprawna komenda! Dopuszczalne sa: f <x> <y> lub r <x> <y>\n");
                Sleep(1000);
            }
        }else{
            printf("Wspolrzedne poza plansza!\n");
            Sleep(1000);
        }
        system("cls");
        print_board(board, r, c, *points, flags, 0);
    }
    fclose(file);

    if(are_all_read(board, r, c) == 1) {
        printf("Wygrana!\n");
        print_board(board, r, c, *points, flags, 1);
    }
}