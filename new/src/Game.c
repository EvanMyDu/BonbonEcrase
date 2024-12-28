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

int rang_suppression[100];
static int nombre_consecutif = 0;

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

int deja_enregistrer(int indice_echange) {
    for (int i = 0; i < 100; i++) {
        if (indice_echange == rang_suppression[i]) {
            return 1;
        }
    }
    return 0;
}

void check_bonbon_alentours(int indice_echange) {
    int temp_indice_echange = indice_echange;
    if ((indice_echange%largeur_grille != largeur_grille - 1) && (couleur_boutons[indice_echange] != 0)) {
        while ((indice_echange%largeur_grille < largeur_grille - 1) && (couleur_boutons[indice_echange] == couleur_boutons[indice_echange + 1])) {
            if (deja_enregistrer(indice_echange) == 0) {
                rang_suppression[nombre_consecutif] = indice_echange;
                nombre_consecutif++;
            }
            if (deja_enregistrer(indice_echange + 1) == 0) {
                rang_suppression[nombre_consecutif] = indice_echange + 1;
                nombre_consecutif++;
            }
            indice_echange++;
        }
        indice_echange = temp_indice_echange;
    }
    if ((indice_echange%largeur_grille != 0) && (couleur_boutons[indice_echange] != 0)) {
        while ((indice_echange%largeur_grille > 0) && (couleur_boutons[indice_echange] == couleur_boutons[indice_echange - 1])) {
            if (deja_enregistrer(indice_echange) == 0) {
                rang_suppression[nombre_consecutif] = indice_echange;
                nombre_consecutif++;
            }
            if (deja_enregistrer(indice_echange - 1) == 0) {
                rang_suppression[nombre_consecutif] = indice_echange - 1;
                nombre_consecutif++;
            }
            indice_echange--;
        }
        indice_echange = temp_indice_echange;
    }
    if ((indice_echange >= largeur_grille) && (couleur_boutons[indice_echange] != 0)) {
        while ((indice_echange >= largeur_grille) && (couleur_boutons[indice_echange] == couleur_boutons[indice_echange - largeur_grille])) {
            if (deja_enregistrer(indice_echange) == 0) {
                rang_suppression[nombre_consecutif] = indice_echange;
                nombre_consecutif++;
            }
            if (deja_enregistrer(indice_echange - largeur_grille) == 0) {
                rang_suppression[nombre_consecutif] = indice_echange - largeur_grille;
                nombre_consecutif++;
            }
            indice_echange = indice_echange - largeur_grille;
        }
        indice_echange = temp_indice_echange;
    }
    if ((indice_echange <= hauteur_grille*largeur_grille - largeur_grille - 1) && (couleur_boutons[indice_echange] != 0)) {
        while ((indice_echange <= hauteur_grille*largeur_grille - largeur_grille - 1) && (couleur_boutons[indice_echange] == couleur_boutons[indice_echange + largeur_grille])) {
            if (deja_enregistrer(indice_echange) == 0) {
                rang_suppression[nombre_consecutif] = indice_echange;
                nombre_consecutif++;
            }
            if (deja_enregistrer(indice_echange + largeur_grille) == 0) {
                rang_suppression[nombre_consecutif] = indice_echange + largeur_grille;
                nombre_consecutif++;
            }
            indice_echange = indice_echange + largeur_grille;
        }
        indice_echange = temp_indice_echange;
    }
}

void check_bonbon_identiques(int indice_echange) {
    check_bonbon_alentours(indice_echange);
}

void supprimer_bonbon(int indice_echange) {
    if (nombre_consecutif >= 4) {
        for (int i = 0; i < nombre_consecutif; i++) {
            couleur_boutons[rang_suppression[i]] = 0;
        }
        nombre_consecutif = 0;
    }
    else {
        nombre_consecutif = 0;
    }
}

void reinitialiser_tableau(int tab[]) {
    for (int i = 0; i < 12; i++) {
        tab[i] = 0;
    }
}

void echange_bonbon(int indice_echange) {
    int temp_couleur = couleur_boutons[indice_clicked];
    if (((((indice_echange == indice_clicked + 1) || (indice_echange == indice_clicked - 1)) || ((indice_echange == (indice_clicked - largeur_grille))) || (indice_echange == (indice_clicked + largeur_grille)))) && ((couleur_boutons[indice_echange] != (couleur_boutons[indice_clicked])) && (couleur_boutons[indice_echange] != 0))) {
        couleur_boutons[indice_clicked] = couleur_boutons[indice_echange];
        couleur_boutons[indice_echange] = temp_couleur;
    }
    else {
        clicked = 0;
    }
}

void tomber_bonbon() {
    for (int i = 0; i < largeur_grille; i++) {
        for (int j = hauteur_grille - 1; j >= 1; j--) {
            if (couleur_boutons[i + j*largeur_grille] == 0) {
                int temp_couleur = couleur_boutons[i + (j-1)*largeur_grille];
                couleur_boutons[i + (j-1)*largeur_grille] = 0;
                couleur_boutons[i + j*largeur_grille] = temp_couleur;
            }
        }
    }
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
            if (gamemode == 1) {
                for (int i = 0; i < largeur_grille*hauteur_grille; i++) {
                    reinitialiser_tableau(rang_suppression);
                    check_bonbon_identiques(i);
                    supprimer_bonbon(i);
                    reinitialiser_tableau(rang_suppression);
                    tomber_bonbon();
                }
            }
            if (gamemode == 2) {
                if (current - start >= 2) {
                    remonter_couleur();
                    ajouter_ligne();
                    start = current;
                }
                for (int i = 0; i < largeur_grille*hauteur_grille; i++) {
                    reinitialiser_tableau(rang_suppression);
                    check_bonbon_identiques(i);
                    supprimer_bonbon(i);
                    reinitialiser_tableau(rang_suppression);
                    tomber_bonbon();
                }
            }
        }
    }
    SDL_Quit(); //Si la boucle de jeu s'arrête on quitte SDL
    exit(EXIT_SUCCESS);
}
