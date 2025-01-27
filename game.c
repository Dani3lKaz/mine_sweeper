#include <stdio.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

#include "board.h"

//Funkcja czekania
void w(int sec) {
#ifdef _WIN32
    Sleep(sec * 1000);
#else
    sleep(sec);
#endif
}

//Funkcja sprawdzająca czy wszystkie pola (niebędące minami) zostały odsłonięte
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

//Funkcja odsłaniająca wybrane pole oraz wszystkie sąsiadujące z nią jeżeli jej nr to 0
//mode oznacza tryb w jakim jest uruchamiana funkcja (0 - dla pierwszego polecenia, 1 - dla wszystkich pozostałych)
void read_fields(Field **board, int r, int c, int x, int y, int mode, int *points) {
    if(x < 0 || x >= r || y < 0 || y >= c) {
        return;
    }

    if(board[x][y].isread == 1 || board[x][y].isbomb == 1){
        return;
    }
    //Odczytanie pola
    board[x][y].isread = 1;
    (*points)++;

    //Rekurencyjne odsłanianie kolejnych pól
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

//Wykonywanie komend - dla programu obsługiwanego przez użytkownika
int execute_commands(Field **board, int r, int c, int mines, int *points, int multiplier) {
    char com;
    int x;
    int y;
    int flags = mines;

    clear();
    print_board(board, r, c, *points, flags, 0);

    while(are_all_read(board, r, c) == 0) {
        //Pobranie komendy od użytkownika i wykonanie odpowiedniej operacji
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
                    //Wygenerowanie min po pierwszym odczycie
                    generate_mines(board, r, c, mines, x-1, y-1);
                    read_fields(board, r, c, x-1, y-1, 0, points);
                }else{
                    if(board[x-1][y-1].isflag == 0 && board[x-1][y-1].isbomb == 1) {
                        //Wyświetlenie planszy z bombami w przypadku porażki
                        print_board(board, r, c, *points * multiplier, flags, 1);
                        return 0;
                    }else if(board[x-1][y-1].isread == 0 && board[x-1][y-1].isflag == 0) {
                        read_fields(board, r, c, x-1, y-1, 1, points);
                    }
                }
            }else{
                printf("Niepoprawna komenda! Dopuszczalne sa: f <x> <y> lub r <x> <y>\n");
                w(2);
            }
        }else{
            printf("Wspolrzedne poza plansza!\n");
            w(2);
        }
        clear();
        print_board(board, r, c, *points * multiplier, flags, 0);
    }
    print_board(board, r, c, *points * multiplier, flags, 1);
    return 1;
}

//Wykonywanie komend czytanych z pliku - gdy program został uruchomiony z flagą -f
void execute_commands_from_file(const char *filename, Field **board, int r, int c, int *points, int flags) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Nie udalo sie otworzyc pliku z komendami.\n");
        return;
    }

    char com;
    int x;
    int y;
    int steps = 0;
    char ch;
    
    //Przesunięcie kursora do miejsca z komendami
    while ((ch = getc(file)) != EOF) {
        if (ch == 'r' || ch == 'f') {
            break;
        }
    }

    fseek(file, -1, SEEK_CUR);

    //Odczytywanie komend
    while (fscanf(file, " %c %d %d", &com, &x, &y) == 3) {
        w(1);
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
                    clear();
                    print_board(board, r, c, *points, flags, 1);
                    printf("Porazka! Trafiono na mine! Liczba poprawnych krokow: %d\n", steps);
                    return;
                }else if(board[x-1][y-1].isread == 0 && board[x-1][y-1].isflag == 0) {
                    steps++;
                    read_fields(board, r, c, x-1, y-1, 1, points);
                }
            }else{
                printf("Niepoprawna komenda! Dopuszczalne sa: f <x> <y> lub r <x> <y>\n");
                w(2);
            }
        }else{
            printf("Wspolrzedne poza plansza!\n");
            w(2);
        }
        clear();
        print_board(board, r, c, *points, flags, 0);
    }
    
    fclose(file);

    if(are_all_read(board, r, c) == 1) {
        clear();
        print_board(board, r, c, *points, flags, 1);
        printf("Wygrana! Liczba poprawnych krokow: %d\n", steps);
    }
}