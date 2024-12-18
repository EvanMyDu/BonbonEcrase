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
    int xplay = GetSystemMetrics(SM_CXSCREEN)/2-147, yplay = GetSystemMetrics(SM_CYSCREEN)/2 -142;
    int xscore =GetSystemMetrics(SM_CXSCREEN)/2-147, yscore = GetSystemMetrics(SM_CYSCREEN)/2 ;
    int xquitter =GetSystemMetrics(SM_CXSCREEN)/2-144, yquitter = GetSystemMetrics(SM_CYSCREEN)/2 + 142;
    int xtitre = GetSystemMetrics(SM_CXSCREEN)/2-550, ytitre = -50;
    SDL_RenderClear(renderer);
    SDL_Texture *background = AfficheImage(renderer,"../image/background.png", 0, 0), *bouton = AfficheImage(renderer, "../image/playbouton.png",xplay ,yplay), *titre = AfficheImage(renderer, "../image/titre.png",xtitre ,ytitre), *scorebouton = AfficheImage(renderer, "../image/scorebouton.png", xscore, yscore), *quitter = AfficheImage(renderer, "../image/quitterbouton.png", xquitter, yquitter);
    CreerBoutonMenu(renderer, xplay, yplay,294, 84, 0);
    CreerBoutonMenu(renderer, xplay, yscore,294, 84, 1);
    CreerBoutonMenu(renderer, xquitter, yquitter,294, 84, 1);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(bouton);
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(titre);
    SDL_DestroyTexture(quitter);
    SDL_DestroyTexture(scorebouton);
}

void ActualiserFenetreChoixGrille(SDL_Renderer *renderer) {

}

void ActualiserFenetreJeu(SDL_Renderer *renderer) {
    SDL_RenderClear(renderer);
    AfficheImage(renderer, "../image/adlaurent.jpg",600 ,435);
    SDL_RenderPresent(renderer);
}