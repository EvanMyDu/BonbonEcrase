#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <windows.h>
#include "../header/Button.h"
#include "../header/AfficheFenetre.h"

static SDL_Rect buttons_menu[18]; //Définie le tableau avec tout les bouton des menus
static SDL_Rect buttons_game[72]; //Définie le tableau avec tout les bouton des jeux

void enregistrer_boutton(SDL_Rect tab[], SDL_Rect rect, int rang) {
    tab[rang] = rect; //Enregistre un bouton dans une liste à un rang données en paramètres
}

void CreerBoutonMenu(SDL_Renderer* renderer, int x, int y, int width, int height, int numero) {
    SDL_Rect rect = {x, y, width, height}; //Creer un bouton, qui est un rectangle
    enregistrer_boutton(buttons_menu, rect, numero); //Enregistre le bouton dans le tableau des boutons des menus
}

void CreerBoutonJeu(SDL_Renderer* renderer, int x, int y, int width, int height, int numero) {
    SDL_Rect rect = {x, y, width, height}; //Creer un bouton, qui est un rectangle
    enregistrer_boutton(buttons_game, rect, numero); //Enregistre le bouton dans le tableau des boutons du jeu
}

int MouseInRect(SDL_Rect rect) {
    int x, y; //Définit deux entiers qui seront les coordonnées de la souris
    SDL_GetMouseState(&x, &y); //Récupère les coordonnées x et y de la souris
    SDL_Point souris = {x,y}; //Définit un point qui a les coordonnées de la souris
    if (SDL_PointInRect(&souris, &rect)) { //Regarde si la souris, associé à un point, est dans le rectangle rect
        return 1; //return TRUE
    }
    else {
        return 0; //return FALSE
    }
}

int GetButtonPurposeMenu(SDL_Renderer *renderer) {
    for (int i = 0; i < 18; i++) { //
        if (MouseInRect(buttons_menu[i]) == 1) { //regarde quel bouton est cliqué
            if (i == 0) { //i == 0 est l'indice du bouton play
                ActualiserFenetreJeu(renderer);
                return 2;
            }
            if (i == 1) {
                ActualiserFenetreChoixGrille(renderer);
                return 1;
            }
            if (i == 2) {
                SDL_Quit();
            }
        }
    }
    SDL_Quit();
    return 0;
}


int GetButtonPurposeGame(SDL_Renderer *renderer) {
    for (int i = 0; i < 72; i++) {
    }
    return 0;
}

int CheckAllRectMenu() {
    for (int i = 0; i < 3; i++) {
        if (MouseInRect(buttons_menu[i]) == 1) { //Vérifie pour chaque rectangle du menu si la souris est dans un rectangle
            return 1; //return TRUE
        }
    }
    return 0; //return FALSE
}

int CheckAllRectGame(){
    for (int i = 0; i < 3; i++) {
        if (MouseInRect(buttons_game[i]) == 1) { //Vérifie pour chaque rectangle du jeu si la souris est dans un rectangle
            return 1; //return TRUE
        }
    }
    return 0; //return FALSE
}

