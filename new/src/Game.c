#include <stdio.h>
#include <SDL_render.h>
#include <SDL.h>
#include <windows.h>
#include "../header/Game.h"
#include "../header/AfficheFenetre.h"
#include "../header/Button.h"

void creer_grille(int a, int b) { //Prend en paramètres d'entrée une largeur a et une longeur b
    int *grille[8][6]; //Creer une grille de taille a*b
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            printf("%p\t", grille[i][j]);
        }
    }
}

void game_loop() {
    SDL_Init(SDL_INIT_EVERYTHING); //Initialise la bibliotheque SDL
    SDL_Renderer *renderer = AfficheFenetre(); //Associe à un pointeur l'instance du renderer créer par la fonction AfficheFenetre
    int menu = 1; //Le menu vaut 1 donc TRUE, au lancement du programme nous somme dans le menu
    int jeu = 0; //Le jeu vaut 0 donc FALSE, nous ne somme donc pas en jeu
    SDL_bool run = SDL_TRUE; //Tant que ce booléen est TRUE, la boucle de jeu ne s'arrête pas
    while(run){
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) //Si on quitte SDL, on arrête la boucle de jeu
            {
                run = SDL_FALSE;
            }
            if (menu == 1 || menu == 2 || menu == 3) {
                if ((event.type == SDL_MOUSEBUTTONDOWN) && (CheckAllRectMenu(renderer) == 1)) { //Regarde si le clic-gauche de la souris est pressé et que la souris se trouve dans un rectangle du menu
                    menu = GetButtonPurposeMenu(renderer); //Détermine quel bouton a été cliqué et modifie la valeur de menu en fonction de la fonction du bouton
                }

            }
            if ((event.type == SDL_MOUSEBUTTONDOWN) && (CheckAllRectGame(renderer) == 1)) { //Regarde si le clic-gauche de la souris est pressé et que la souris se trouve dans un rectangle du jeu
                jeu = GetButtonPurposeGame(renderer);
            }
        }
        if (menu == 1) { //Si on est dans le menu
            ActualiserFenetreMenu(renderer); //Affiche le menu
        }
        if (menu == 0) { //Si on est plus dans le menu
            jeu = 1; //Lance le jeu
        }
        if (jeu == 1) { //Si on est dans le jeu
            ActualiserFenetreJeu(renderer); //Affiche le jeu
        }
    }
    SDL_Quit(); //Si la boucle de jeu s'arrête on quitte SDL
}