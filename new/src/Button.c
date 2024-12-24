#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <windows.h>
#include "../header/Button.h"
#include "../header/AfficheFenetre.h"
#include "../header/Game.h"
#include <time.h>

static SDL_Rect buttons_menu[20]; //Définie le tableau avec tout les bouton des menus
SDL_Rect buttons_game[72]; //Définie le tableau avec tout les bouton des jeux
int largeur_grille;
int hauteur_grille;
int couleur_boutons[72];

void enregistrer_boutton(SDL_Rect tab[], SDL_Rect rect, int rang) {
    tab[rang] = rect; //Enregistre un bouton dans une liste à un rang données en paramètres
}

int choix_couleur() {
    int couleur = (rand()%4)+1;
    return couleur;
}

void CreerBoutonMenu(SDL_Renderer* renderer, int x, int y, int width, int height, int numero) {
    SDL_Rect rect = {x, y, width, height}; //Creer un bouton, qui est un rectangle
    enregistrer_boutton(buttons_menu, rect, numero); //Enregistre le bouton dans le tableau des boutons des menus
}

void CreerBoutonJeu(SDL_Renderer* renderer, int x, int y, int width, int height, int numero) {
    SDL_Rect rect = {x, y, width, height}; //Creer un bouton, qui est un rectangle
    enregistrer_boutton(buttons_game, rect, numero); //Enregistre le bouton dans le tableau des boutons du jeu
}

void creer_grille(SDL_Renderer* renderer, int gamemode) {
    srand(time(NULL));
    if (gamemode == 1) {
        for (int i = 0; i < (largeur_grille*hauteur_grille); i++) {
            CreerBoutonJeu(renderer, (((GetSystemMetrics(SM_CXSCREEN)/(largeur_grille+1))*(i%largeur_grille)) + (GetSystemMetrics(SM_CXSCREEN)/(largeur_grille+1))), (GetSystemMetrics(SM_CYSCREEN)/hauteur_grille+2)*(i/largeur_grille), 50, 50, i);
            couleur_boutons[i] = choix_couleur();
        }
    }
    if (gamemode == 2) {
        for (int i = 0; i < (largeur_grille*hauteur_grille); i++) {
            CreerBoutonJeu(renderer, (((GetSystemMetrics(SM_CXSCREEN)/(largeur_grille+1))*(i%largeur_grille)) + (GetSystemMetrics(SM_CXSCREEN)/(largeur_grille+1))), (GetSystemMetrics(SM_CYSCREEN)/hauteur_grille+2)*(i/largeur_grille), 50, 50, i);
        }
        for (int j = (largeur_grille*hauteur_grille) - 1; j > ((hauteur_grille-3)*largeur_grille) - 1; j--) {
            couleur_boutons[j] = choix_couleur();
        }
    }
}

void remonter_couleur() {
    for (int i = 0; i < ((largeur_grille*hauteur_grille) - largeur_grille); i++) {
        couleur_boutons[i] = couleur_boutons[i + largeur_grille];
        couleur_boutons[i+largeur_grille] = 0;
    }
}

void ajouter_ligne() {
    for (int i = ((largeur_grille*hauteur_grille) - largeur_grille); i < (largeur_grille*hauteur_grille); i++) {
        couleur_boutons[i] = choix_couleur();
    }
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

int GetButtonPurposeMenu(SDL_Renderer *renderer, int rang_d, int rang_f, int state) {
    int a = 0;
    for (int i = rang_d; i < rang_f + 1; i++) { //
        if (MouseInRect(buttons_menu[i]) == 1) { //regarde quel bouton est cliqué
            if (i == 0) { //i == 0 est l'indice du bouton play
                return 2;
            }
            if (i == 1) {//i  == 1 est l'indice du score
                return 4;
            }
            if (i == 2) {//i == 2 est l'indice pour quitter
                SDL_Quit();
                exit(EXIT_SUCCESS);
            }
            if (i == 3) {
                return SetGameMode(2); //Set le gamemode en rush
            }
            if (i == 4) {
                return SetGameMode(1); //Set le gamemode en puzzle
            }
            if (i>= 5 && i<=20) {
                hauteur_grille = ((i-5)/3)+8;
                largeur_grille = ((i-5)%3)+4;
                return 3;
            }
            if (i == 1000){
                return 1;
            }
        }
    }
    return state;
}


int GetButtonPurposeGame(SDL_Renderer *renderer, int rang_d, int rang_f) {
    for (int i = rang_d; i < rang_f + 1; i++) {
    }
    return 0;
}

int CheckAllRectMenu() {
    for (int i = 0; i < 20; i++) {
        if (MouseInRect(buttons_menu[i]) == 1) { //Vérifie pour chaque rectangle du menu si la souris est dans un rectangle
            return 1; //return TRUE
        }
    }
    return 0; //return FALSE
}

int CheckAllRectGame(){
    for (int i = 0; i < 72; i++) {
        if (MouseInRect(buttons_game[i]) == 1) { //Vérifie pour chaque rectangle du jeu si la souris est dans un rectangle
            return 1; //return TRUE
        }
    }
    return 0; //return FALSE
}

