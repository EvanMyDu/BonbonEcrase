#include <stdio.h>
#include <SDL_render.h>
#include <SDL.h>
#include <windows.h>
#include "../header/Game.h"
#include "../header/AfficheFenetre.h"
#include "../header/Button.h"

void creer_grille(int a, int b) {
    int *grille[8][6];
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            printf("%p\t", grille[i][j]);
        }
    }
}

void game_loop() {
    int x, y;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Renderer *renderer = AfficheFenetre();
    int menu = 1;
    int jeu = 0;
    SDL_bool run = SDL_TRUE;
    while(run){
        SDL_GetMouseState(&x, &y);
        SDL_Point souris = {x, y};
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
            {
                run = SDL_FALSE;
            }
            if (menu == 1) {
                if ((event.type == SDL_MOUSEBUTTONDOWN) && (CheckAllRectMenu(renderer) == 1)) {
                    jeu = 1;
                    menu = 0;
                }
            }
        }
        if (menu == 1) {
            ActualiserFenetreMenu(renderer);
        }
        if (jeu == 1) {
            ActualiserFenetreJeu(renderer);
        }
    }
    SDL_Quit();
}