#include <stdio.h>
#include <SDL_render.h>
#include <SDL.h>
#include <windows.h>
#include "../header/Game.h"
#include "../header/AfficheFenetre.h"
#include "../header/Button.h"

int SetGameMode(int a) {
    return a;
}

void print_grille(int grille[]) {
    for (int i = 0; i < 72; i++) {
        printf("couleur = %d ", couleur_boutons[i]);
    }
}

void game_loop() {
    SDL_Init(SDL_INIT_EVERYTHING); //Initialise la bibliotheque SDL
    SDL_Renderer *renderer = AfficheFenetre(); //Associe à un pointeur l'instance du renderer créer par la fonction AfficheFenetre
    int menu = 1; //Le menu vaut 1 donc TRUE, au lancement du programme nous somme dans le menu
    int jeu = 0; //Le jeu vaut 0 donc FALSE, nous ne somme donc pas en jeu
    int gamemode = 0; //Le gamemode vaut 0 donc nous sommes pas en gamemode
    SDL_bool run = SDL_TRUE; //Tant que ce booléen est TRUE, la boucle de jeu ne s'arrête pas
    while(run) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) //Si on quitte SDL, on arrête la boucle de jeu
            {
                run = SDL_FALSE;
            }
            if (menu == 3) {
                if ((event.type == SDL_MOUSEBUTTONDOWN) && (CheckAllRectMenu() == 1)) { //Regarde si le clic-gauche de la souris est pressé et que la souris se trouve dans un rectangle du menu
                    gamemode = GetButtonPurposeMenu(renderer, 3, 4, menu); //Détermine quel bouton a été cliqué et modifie la valeur de menu en fonction de la fonction du bouton
                    if (gamemode == 1 || gamemode == 2) {
                        jeu = 1;
                        menu = 0;
                    }
                    if (gamemode == 1) {
                        creer_grille(renderer, 1);
                    }
                    if (gamemode == 2) {
                        creer_grille(renderer, 2);
                    }
                }
            }
            if (menu == 2) {
                if ((event.type == SDL_MOUSEBUTTONDOWN) && (CheckAllRectMenu() == 1)) { //Regarde si le clic-gauche de la souris est pressé et que la souris se trouve dans un rectangle du menu
                    //Détermine quel bouton a été cliqué et modifie la valeur de menu en fonction de la fonction du bouton
                    menu = GetButtonPurposeMenu(renderer, 5, 20, menu);
                }
            }
            if (menu == 1) {
                if ((event.type == SDL_MOUSEBUTTONDOWN) && (CheckAllRectMenu() == 1)) { //Regarde si le clic-gauche de la souris est pressé et que la souris se trouve dans un rectangle du menu
                    menu = GetButtonPurposeMenu(renderer, 0, 2, menu); //Détermine quel bouton a été cliqué et modifie la valeur de menu en fonction de la fonction du bouton
                }
            }
            if (jeu == 1){
                if ((event.type == SDL_MOUSEBUTTONDOWN) && (CheckAllRectGame() == 1)) {
                    //Regarde si le clic-gauche de la souris est pressé et que la souris se trouve dans un rectangle du jeu
                    jeu = GetButtonPurposeGame(renderer, 0, 72);
                }
            }
        }
        if (menu == 1) { //Si on est dans le menu
            ActualiserFenetreMenu(renderer); //Affiche le menu
        }
        if (menu == 3) { //Si on est plus dans le menu
            ActualiserFenetreChoixMode(renderer);
        }
        if (menu == 2) {
            ActualiserFenetreChoixGrille(renderer);
        }
        if (jeu == 1) { //Si on est dans le jeu
            ActualiserFenetreJeu(renderer); //Affiche le jeu*
        }
    }
    SDL_Quit(); //Si la boucle de jeu s'arrête on quitte SDL
    exit(EXIT_SUCCESS);
}
