#include <stdio.h>
#include <assert.h>
#include "../include/board.h"

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

int main() {
    test_generate_mines();
    printf("✅ Wszystkie testy OK\n");
}