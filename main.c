#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h> 
#include "board.h"
#include "game.h"
#include "results.h"

int main(int argc, char **argv) {
    
    int opt;
    char *filename = NULL;
    int read_from_file = 0;

    while ((opt = getopt(argc, argv, "f:")) != -1) {
        switch (opt) {
            case 'f':
                read_from_file = 1;
                filename = optarg;
                break;
            case '?':
                fprintf(stderr, "Niepoprawna opcja. Uzyj -f <nazwa_pliku> aby wczytac plansze z pliku.\n");
                return 1;
            default:
                fprintf(stderr, "Nieznana opcja.\n");
                return 1;
        }
    }
    
    
    if(read_from_file){
        if(strcmp(argv[1], "-f") != 0) {
            fprintf(stderr, "Nieprawidlowa flaga! Aby uruchomic program w trybie czytania pliku uzyj flagi -f\n");
            return 1;
        }
        int r = 0;
        int c = 0;
        int mines = 0;
        int points = 0;
        Field **board;
        board = load_board(argv[2], &r, &c, &mines);
        execute_commands_from_file(argv[2], board, r, c, &points, mines);
    }else{
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
        int result = execute_commands(board, level.r, level.c, level.mines, &points, level.multiplier);

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
    }
    
    return 0;
}
