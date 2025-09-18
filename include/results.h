#ifndef _RESULTS_H
#define _RESULTS_H

//Struktura zawierająca dane gracza
typedef struct {
    char name[50];
    int points;
}Player;

int compare_results(const void *a, const void *b);
int load_result(const char *filename, Player players[]);
void add_new_result(Player players[], int *count, const char *name, int points);
void save_result(const char *filename, Player players[], int count);

#endif