#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h> 
#include <locale.h>
#include "../include/board.h"
#include "../include/game.h"
#include "../include/results.h"

int main(int argc, char **argv) {
    setlocale(LC_ALL, "pl_PL.UTF-8");
    
    int opt;
    char *filename = NULL;
    int read_from_file = 0;

    //Sprawdzenie trybu uruchomienia pliku
    while ((opt = getopt(argc, argv, "f:")) != -1) {
        switch (opt) {
            case 'f':
                read_from_file = 1;
                filename = optarg;
                break;
            case '?':
                fprintf(stderr, "Niepoprawna opcja. Użyj -f <nazwa_pliku> aby wczytać planszę z pliku.\n");
                return 1;
        }
    }
    
    if(read_from_file){
        //Czytanie planszy i komend z pliku
        int r = 0;
        int c = 0;
        int mines = 0;
        int points = 0;
        Field **board;

        board = load_board(filename, &r, &c, &mines);
        execute_commands_from_file(filename, board, r, c, &points, mines);

        free_board(board, r);
    }else{
        //Rozgrywka użytkownika
        if(argc < 2) {
            printf("Nie wskazano pliku zapisu wyników!\n\nTworzę plik results.txt ...\n\n");
            filename = "results.txt";
        }else{
            filename = argv[1];
        }

        Field **board = NULL;
        Difficulty level;
        int points = 0;

        srand(time(NULL));
        //Wybór poziomu trudności
        level = choose_difficulty();
        if(level.c * level.r < level.mines || level.mines < 1 || level.r < 4 || level.c < 4) {
            fprintf(stderr, "Nieprawidłowe dane planszy. Spróbuj ponownie\n");
            return 1;
        }

        //Generowanie planszy
        board = generate_board(level.r, level.c);

        if(board == NULL) {
            fprintf(stderr, "Nie udało się wygenerować planszy!\n");
        }

        //Gra w sapera (odczytywanie komend użytkownika)
        int result = execute_commands(board, level.r, level.c, level.mines, &points, level.multiplier);

        points *= level.multiplier;

        if(result == 1) {
            printf("Wygrana! Twój wynik to: %d\n", points);
        }else{
            printf("Porażka! Trafiłes na minę! Twój wynik to: %d\n", points);
        }

        //Zapisywanie wyniku gracza do pliku
        Player players[5];
        char name[50];
        int player_count;
        player_count = load_result(filename, players);


        printf("Podaj swoją nazwę: ");
        scanf("%49s", name);
        add_new_result(players, &player_count, name, points);
        save_result(filename, players, player_count);

        //Wypisanie 5 najlepszych graczy
        printf("TOP 5 najlepszych graczy:\n");
        int i;
        for(i = 0; i < player_count; i++) {
            printf("%d. %s  %d\n", i+1, players[i].name, players[i].points);
        }

        free_board(board, level.r);
    }
    return 0;
}
