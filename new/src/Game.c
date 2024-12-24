#include <stdio.h>
#include <SDL_render.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <windows.h>
#include <time.h>
#include "../header/Game.h"
#include "../header/AfficheFenetre.h"
#include "../header/Button.h"
#include "../header/score.h"

int SetGameMode(int a) {
    return a;
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

void echange_bonbon(int indice_echange) {
    int temp_couleur = couleur_boutons[indice_clicked];
    couleur_boutons[indice_clicked] = couleur_boutons[indice_echange];
    couleur_boutons[indice_echange] = temp_couleur;
}

void game_loop() {
    time_t start = time(NULL);
    time_t current;
    SDL_Init(SDL_INIT_EVERYTHING); //Initialise la bibliotheque SDL
    TTF_Init();
    SDL_Renderer *renderer = AfficheFenetre(); //Associe à un pointeur l'instance du renderer créer par la fonction AfficheFenetre
    int menu = 1; //Le menu vaut 1 donc TRUE, au lancement du programme nous somme dans le menu
    int jeu = 0; //Le jeu vaut 0 donc FALSE, nous ne somme donc pas en jeu
    int gamemode = 0; //Le gamemode vaut 0 donc nous sommes pas en gamemode
    SDL_bool run = SDL_TRUE; //Tant que ce booléen est TRUE, la boucle de jeu ne s'arrête pas
    sauvegarder_score(2500, "Evan");
    sauvegarder_score(200, "Alice"); // Exemple : Ajouter un score
    sauvegarder_score(150, "Bob");   // Exemple : Ajouter un autre score
    sauvegarder_score(300, "Charlie");
    sauvegarder_score(100, "Diane");




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
            if (menu == 4) {
                if ((event.type == SDL_MOUSEBUTTONDOWN) && (CheckAllRectGame() == 1)) {
                    menu = GetButtonPurposeMenu(renderer, 21, 21, menu);
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
            if (jeu == 1) {
                if ((event.type == SDL_MOUSEBUTTONDOWN) && (CheckAllRectGame() == 1)) { //Regarde si le clic-gauche de la souris est pressé et que la souris se trouve dans un rectangle du jeu
                    GetButtonPurposeGame(renderer);
                }
            }

        }
        if (menu == 4) {
            ActualiserFenetreScore(renderer);
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
            current = time(NULL);
            if (current - start >= 15) {
                remonter_couleur();
                ajouter_ligne();
                start = current;
            }
        }
    }
    SDL_Quit(); //Si la boucle de jeu s'arrête on quitte SDL
    exit(EXIT_SUCCESS);
}
