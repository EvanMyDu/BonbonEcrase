#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <windows.h>
#include "../header/Button.h"
#include "../header/AfficheFenetre.h"

static SDL_Rect buttons_menu[3];
static SDL_Rect buttons_game[72];

void enregistrer_boutton(SDL_Rect tab[], SDL_Rect rect, int rang) {
    tab[rang] = rect;
}

void CreerBoutonMenu(SDL_Renderer* renderer, int x, int y, int width, int height, int numero) {
    SDL_Rect rect = {x, y, width, height};
    enregistrer_boutton(buttons_menu, rect, numero);
}

void CreerBoutonJeu(SDL_Renderer* renderer, int x, int y, int width, int height, int numero) {
    SDL_Rect rect = {x, y, width, height};
    enregistrer_boutton(buttons_game, rect, numero);
}

int MouseInRect(SDL_Rect rect) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    SDL_Point souris = {x,y};
    if (SDL_PointInRect(&souris, &rect)) {
        return 1;
    }
    else {
        return 0;
    }
}

void GetButtonPurposeMenu(int i) {
    if (i == 2) {
        SDL_Quit();
    }
}

void GetButtonPurposeGame(int i) {
}

int CheckAllRectMenu() {
    for (int i = 0; i < 3; i++) {
        if (MouseInRect(buttons_menu[i]) == 1) {
            return 1;
        }
    }
    return 0;
}

int CheckAllRectGame() {
    for (int i = 0; i < 3; i++) {
        if (MouseInRect(buttons_game[i]) == 1) {
            return 1;
        }
    }
    return 0;
}

