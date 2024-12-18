#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <windows.h>
#include "../header/Button.h"

static SDL_Rect bouttons[3];

void enregistrer_boutton(SDL_Rect tab[], SDL_Rect rect, int rang) {
    tab[rang] = rect;
}

void CreerBouton(SDL_Renderer* renderer, int x, int y, int width, int height, int numero) {
    SDL_Rect rect = {x, y, width, height};
    enregistrer_boutton(bouttons, rect, numero);
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

int CheckAllRect() {
    for (int i = 1; i < 3; i++) {
        if (MouseInRect(bouttons[i]) == 1) {
            return i;
        }
    }
    return 0;
}
