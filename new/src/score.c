#include "../header/score.h"
#include <stdlib.h>
#include <stdio.h>
#include <SDL_ttf.h>

// Variable statique pour stocker le score courant
static int score = 0;

// Fonction pour sauvegarder le score dans un fichier
void sauvegarder_score(char nom[]) {
    // Ouvre le fichier texte en mode ajout
    FILE *sauvegarde_points = fopen("../texte/sauvegarde.txt", "a");

    // Vérifie si l'ouverture du fichier a échoué
    if (sauvegarde_points == NULL) {
        exit(1); // Quitte le programme avec un code d'erreur
    }

    // Écrit le nom et le score dans le fichier
    fprintf(sauvegarde_points, " %s  %d\n", nom, score);

    // Ferme le fichier après l'écriture
    fclose(sauvegarde_points);
    score = 0; // Réinitialise le score après la sauvegarde
}

// Fonction pour attribuer des points en fonction de la chaîne et de la consécutivité
void donner_points(int longueur_chaine, int consecutif) {
    // Calcul du score basé sur la formule donnée
    score = score + ((consecutif + 1)*((longueur_chaine-1)*(longueur_chaine-1)));
}

// Fonction pour lire les scores enregistrés depuis un fichier
int lire_score(int taille_max, Joueur joueur[]) {
    // Ouvre le fichier en mode lecture
    FILE *lire_points = fopen("../texte/sauvegarde.txt", "r");

    // Vérifie si le fichier s'est ouvert correctement
    if (lire_points == NULL) {
        perror("Erreur lors de l'ouverture du fichier"); // Affiche une erreur
        exit(1); // Quitte le programme avec un code d'erreur
    }

    int i = 0; // Initialisation de l'index pour les joueurs
    while (i < taille_max) {
        // Lit un nom et un score depuis le fichier
        int result = fscanf(lire_points, " %49s %d\n", joueur[i].nom, &joueur[i].score);

        // Si la lecture échoue ou atteint la fin du fichier, arrête la boucle
        if (result != 2) {
            if (result == EOF) {
                break; // Fin du fichier
            } else {
                printf("Erreur de format dans le fichier de scores.\n"); // Erreur de format
                break;
            }
        }
        i++; // Passe au joueur suivant
    }

    fclose(lire_points); // Ferme le fichier après la lecture
    return i; // Retourne le nombre de scores lus
}

// Fonction pour comparer deux scores pour un tri décroissant
int comparer_scores(const void *a, const void *b) {
    Joueur *j1 = (Joueur *)a;
    Joueur *j2 = (Joueur *)b;
    return j2->score - j1->score; // Retourne la différence pour un tri décroissant
}

// Fonction pour afficher les scores dans la fenêtre SDL
void affichescore(SDL_Renderer *renderer) {
    // Charger la police depuis un fichier avec une taille de 30
    TTF_Font *Font = TTF_OpenFont("../police/arialbd.ttf", 30);

    // Lire et trier les scores
    Joueur joueurs[100];
    int nb_joueurs = lire_score(100, joueurs);

    // Vérifie si aucun score n'est disponible
    if (nb_joueurs == 0) {
        printf("Aucun score à afficher.\n");
        TTF_CloseFont(Font); // Ferme la police avant de quitter
        return;
    }

    // Trie les scores par ordre décroissant
    qsort(joueurs, nb_joueurs, sizeof(Joueur), comparer_scores);

    // Limite l'affichage au top 10 scores
    if (nb_joueurs > 10) {
        nb_joueurs = 10;
    }

    // Définir la couleur blanche pour le texte
    SDL_Color couleurBlanche = {255, 255, 255, 255};

    // Initialise les dimensions et la position du rectangle de texte
    SDL_Rect TextRect;
    TextRect.x = 100; // Position X
    TextRect.y = 100; // Position Y
    TextRect.w = 0;   // Largeur ajustée automatiquement
    TextRect.h = 0;   // Hauteur ajustée automatiquement

    // Affiche chaque score
    for (int i = 0; i < nb_joueurs; i++) {
        // Crée une chaîne pour afficher chaque score avec son rang
        char scoreTexte[100];
        snprintf(scoreTexte, sizeof(scoreTexte), "%d. %s : %d", i + 1, joueurs[i].nom, joueurs[i].score);

        // Crée une surface pour le texte
        SDL_Surface *TextSurface = TTF_RenderText_Blended_Wrapped(Font, scoreTexte, couleurBlanche, 800);

        // Crée une texture à partir de la surface
        SDL_Texture *TextTexture = SDL_CreateTextureFromSurface(renderer, TextSurface);

        // Ajuste la taille du rectangle à celle du texte
        TextRect.w = TextSurface->w;
        TextRect.h = TextSurface->h;

        // Affiche la texture dans le renderer
        SDL_RenderCopy(renderer, TextTexture, NULL, &TextRect);

        // Libère les ressources associées au texte
        SDL_FreeSurface(TextSurface);
        SDL_DestroyTexture(TextTexture);

        // Passe à la ligne suivante pour le prochain score
        TextRect.y += 50; // Espace vertical entre les scores
    }

    // Met à jour l'affichage
    SDL_RenderPresent(renderer);

    // Ferme la police après utilisation
    TTF_CloseFont(Font);
}