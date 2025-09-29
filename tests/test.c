#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../include/board.h"
#include "../include/game.h"
#include "../include/results.h"

void test_generate_mines() {
    Difficulty d = {10, 10, 18, 1};
    Field** f = generate_board(d.r, d.c);
    generate_mines(f, d.r, d.c, d.mines, 5, 5);
    int mines = 0;
    for(int i = 0; i < d.c; i++) {
        for(int j = 0; j < d.r; j++) {
            if(f[i][j].isbomb) {
                mines++;
            }
        }
    }
    assert(mines == 18);
    printf("test_generate_board OK\n");
}

void test_all_fields_read() {
    Field** board = generate_board(2, 2);
    board[0][0].isread = 1;
    board[0][1].isread = 1;
    board[1][0].isbomb = 1;
    board[1][1].isread = 1;

    assert(all_fields_read(board, 2, 2) == 1);

    board[1][1].isread = 0;
    assert(all_fields_read(board, 2, 2) == 0);
    printf("test_all_fields_read OK\n");
}

void test_add_new_result() {
    Player players[5];
    int count = 0;

    add_new_result(players, &count, "Player1", 10);
    add_new_result(players, &count, "Player2", 20);
    add_new_result(players, &count, "Player3", 15);

    assert(count == 3);
    assert(strcmp(players[0].name, "Player2") == 0);
    assert(players[0].points == 20);
    assert(strcmp(players[1].name, "Player3") == 0);
    assert(players[1].points == 15);
    assert(strcmp(players[2].name, "Player1") == 0);
    assert(players[2].points == 10);

    add_new_result(players, &count, "Player4", 5);
    assert(count == 4);
    assert(strcmp(players[3].name, "Player4") == 0);

    add_new_result(players, &count, "Player5", 30);
    assert(strcmp(players[0].name, "Player5") == 0);
    assert(players[0].points == 30);

    printf("test_add_new_result OK\n");
}

int main() {
    test_generate_mines();
    test_all_fields_read();
    test_add_new_result();
    printf("✅ Wszystkie testy OK\n");
}