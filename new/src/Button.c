#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <windows.h>
#include "../header/Button.h"
#include "../header/Game.h"

// Déclaration des variables globales
static SDL_Rect buttons_menu[21]; // Tableau pour stocker les boutons du menu (21 boutons maximum)
SDL_Rect buttons_game[78];        // Tableau pour stocker les boutons du jeu (78 boutons maximum)
int largeur_grille;               // Largeur de la grille de jeu
int hauteur_grille;               // Hauteur de la grille de jeu
int couleur_boutons[78];          // Tableau pour stocker la couleur des boutons dans le jeu
int indice_clicked;               // Indice du bouton cliqué
int clicked = 0;                   // État de clic (0 = aucun clic, 1 = clic en cours)

// Fonction pour enregistrer un bouton dans un tableau à une position donnée
void enregistrer_boutton(SDL_Rect tab[], SDL_Rect rect, int rang) {
    tab[rang] = rect; // Stocke le rectangle dans le tableau à l'indice spécifié
}

// Fonction pour choisir une couleur aléatoire entre 1 et 4
int choix_couleur() {
    int couleur = (rand()%4)+1; // Génère une couleur entre 1 et 4
    return couleur;
}

// Fonction pour créer un bouton dans le menu
void CreerBoutonMenu(SDL_Renderer* renderer, int x, int y, int width, int height, int numero) {
    SDL_Rect rect = {x, y, width, height}; // Crée un rectangle avec les dimensions spécifiées
    enregistrer_boutton(buttons_menu, rect, numero); // Enregistre le bouton dans le tableau des boutons de menu
}

// Fonction pour créer un bouton dans le jeu
void CreerBoutonJeu(SDL_Renderer* renderer, int x, int y, int width, int height, int numero) {
    SDL_Rect rect = {x, y, width, height}; // Crée un rectangle avec les dimensions spécifiées
    enregistrer_boutton(buttons_game, rect, numero); // Enregistre le bouton dans le tableau des boutons de jeu
}

// Vérifie si la souris est à l'intérieur d'un rectangle donné
int MouseInRect(SDL_Rect rect) {
    int x, y; // Variables pour stocker les coordonnées de la souris
    SDL_GetMouseState(&x, &y); // Récupère la position actuelle de la souris
    SDL_Point souris = {x, y}; // Crée un point avec les coordonnées de la souris
    if (SDL_PointInRect(&souris, &rect)) { // Vérifie si le point est dans le rectangle
        return 1; // Retourne vrai (TRUE)
    }
    else {
        return 0; // Retourne faux (FALSE)
    }
}

// Gère les actions associées aux boutons dans le menu
int GetButtonPurposeMenu(SDL_Renderer *renderer, int rang_d, int rang_f, int state) {
    int a = 0;
    for (int i = rang_d; i < rang_f + 1; i++) { // Parcourt les boutons entre rang_d et rang_f
        if (MouseInRect(buttons_menu[i]) == 1) { // Vérifie si la souris est dans un bouton
            // Actions associées à chaque bouton
            if (i == 0) { // Bouton Play
                return 2;
            }
            if (i == 1) { // Bouton Score
                return 4;
            }
            if (i == 2) { // Bouton Quitter
                SDL_Quit();
                exit(EXIT_SUCCESS);
            }
            if (i == 3) { // Mode Rush
                return SetGameMode(2);
            }
            if (i == 4) { // Mode Puzzle
                return SetGameMode(1);
            }
            if (i >= 5 && i <= 19) { // Sélection de la taille de la grille
                hauteur_grille = ((i-5)/3)+8;
                largeur_grille = ((i-5)%3)+4;
                return 3;
            }
            if (i == 20) { // Retour au menu
                return 1;
            }
        }
    }
    return state; // Retourne l'état inchangé si aucun bouton n'est cliqué
}

// Gère les actions associées aux boutons dans le jeu
void GetButtonPurposeGame(SDL_Renderer *renderer) {
    for (int i = 0; i < 72; i++) { // Parcourt tous les boutons du jeu
        if (MouseInRect(buttons_game[i]) == 1) { // Vérifie si la souris est sur un bouton
            if (couleur_boutons[i] != 0 && clicked == 0) { // Premier clic sur un bouton coloré
                clicked = 1;
                indice_clicked = i; // Stocke l'indice du bouton cliqué
            }
            else if (clicked == 1) { // Deuxième clic pour échanger les boutons
                echange_bonbon(i);
                clicked = 0; // Réinitialise l'état de clic
            }
        }
    }
}

// Vérifie si la souris est dans un des rectangles du menu
int CheckAllRectMenu() {
    for (int i = 0; i < 21; i++) { // Parcourt tous les boutons du menu
        if (MouseInRect(buttons_menu[i]) == 1) { // Vérifie si la souris est sur un bouton
            return 1; // Retourne vrai (TRUE)
        }
    }
    return 0; // Retourne faux (FALSE)
}

// Vérifie si la souris est dans un des rectangles du jeu
int CheckAllRectGame(){
    for (int i = 0; i < 72; i++) { // Parcourt tous les boutons du jeu
        if (MouseInRect(buttons_game[i]) == 1) { // Vérifie si la souris est sur un bouton
            return 1; // Retourne vrai (TRUE)
        }
    }
    return 0; // Retourne faux (FALSE)
}