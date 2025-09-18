#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/results.h"

//Funkcja porównująca wyniki (do qsort)
int compare_results(const void *a, const void *b){
    Player *ca = (Player *)a;
    Player *cb = (Player *)b;
    return cb->points - ca->points;
}

//Funkcja wczytująca dotychczasowe wyniki z pliku
int load_result(const char *filename, Player players[]) {
    FILE *player_list = fopen(filename, "r");
    //Jeśli podany plik nie istnieje to zwraca 0
    if(player_list == NULL) {
        return 0;
    }

    int count = 0;

    while(fscanf(player_list, "%49s %d", players[count].name, &players[count].points) == 2) {
        count++;
        if(count >= 5) {
            break;
        }
    } 
    fclose(player_list);

    return count;
}

//Dodanie nowego wyniku jeżeli kwalifikuje się do TOP 5
void add_new_result(Player players[], int *count, const char *name, int points) {
    
    if(*count < 5) {
        strcpy(players[*count].name, name);
        players[*count].points = points;
        (*count)++;
    }else if(points > players[4].points) {
        strcpy(players[4].name, name);
        players[4].points = points;
    }

    qsort(players, *count, sizeof(Player), compare_results);

    if(*count > 5) {
        *count = 5;
    }
}

//Zapisanie odświeżonej listy w pliku (nadpisanie obecnego lub utworzenie nowego)
void save_result(const char *filename, Player players[], int count) {
    FILE *player_list = fopen(filename, "w");
    if(player_list == NULL) {
        printf("Nie udało się otworzyć pliku do zapisu!\n");
        return;
    }
    
    int i;
    for(i = 0; i < count; i++) {
        fprintf(player_list, "%s  %d\n", players[i].name, players[i].points);
    }

    fclose(player_list);
}