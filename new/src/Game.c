#include <stdio.h>
#include "../header/Game.h"

void creer_grille(int a, int b) {
    int *grille[8][6];
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            printf("%p\t", grille[i][j]);
        }
    }
}

void game_loop() {

}