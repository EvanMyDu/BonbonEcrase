#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <windows.h>
#include "../header/AfficheFenetre.h"
#include "../header/ImageHandler.h"
#include "../header/Button.h"

SDL_Renderer* AfficheFenetre() {
    SDL_Window *window = SDL_CreateWindow("Hello World", SDL_WINDOWPOS_UNDEFINED, 35, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) - 30, SDL_WINDOW_OPENGL);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    return renderer;
}

void ActualiserFenetreMenu(SDL_Renderer *renderer) {
    SDL_RenderClear(renderer);
    AfficheImage(renderer,"../image/background.jpg", 0, 0);
    AfficheImage(renderer, "../image/BoutonRose.png",600 ,435);
    CreerBouton(renderer, 50, 50, 721, 211);
    SDL_RenderPresent(renderer);
}

void ActualiserFenetreJeu(SDL_Renderer *renderer) {
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}