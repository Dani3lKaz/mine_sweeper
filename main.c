#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "board.h"
#include "game.h"
#include "results.h"

int main(int argc, char **argv) {
    if(argc < 2) {
        fprintf(stderr, "Nie podano pliku zapisu wynikow!\n");
        return 1;
    }
    Field **board;
    Difficulty level;
    int points = 0;
    srand(time(NULL));
    level = choose_difficulty();
    if(level.c * level.r < level.mines || level.mines < 1) {
        fprintf(stderr, "Nieprawidlowe dane planszy. Sprobuj ponownie\n");
        return 1;
    }
    printf("r = %d, c = %d, mines = %d\n", level.r, level.c, level.mines);
    board = generate_board(level.r, level.c);
    int result = game(board, level.r, level.c, level.mines, &points, level.multiplier);

    Player players[5];
    char name[50];
    points *= level.multiplier;
    int player_count;
    player_count = load_result(argv[1], players);
    if(result == 1) {
        printf("Wygrana! Twoj wynik to: %d\n", points);
    }else{
        printf("Porazka! Trafiles na mine! Twoj wynik to: %d\n", points);
    }

    printf("Podaj swoja nazwe: ");
    scanf("%49s", &name);
    add_new_result(players, &player_count, name, points);
    save_results(argv[1], players, player_count);

    printf("TOP 5 najlepszych graczy:\n");
    int i;
    for(i = 0; i < player_count; i++) {
        printf("%d. %s  %d\n", i+1, players[i].name, players[i].points);
    }

    free(board);
    
    return 0;
}
