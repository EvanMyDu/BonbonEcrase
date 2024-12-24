#include "../header/score.h"
#include <stdlib.h>
#include <stdio.h>
#include <SDL_ttf.h>



void sauvegarder_score(int score, char nom[]) {

    FILE *sauvegarde_points = fopen("../texte/sauvegarde.txt", "a"); //On ouvre le fichier texte en mode ajout

    if (sauvegarde_points == NULL) { //on vérifie que le fichier s'est bien ouvert
        exit(1);
    }

    fprintf(sauvegarde_points, " %s  %d\n", nom, score); //On écrit ce score dans le fichier sauvegarde.txt

    fclose(sauvegarde_points);//On ferme le fichier
}

int lire_score(int taille_max, Joueur joueur[]) {
    FILE *lire_points = fopen("../texte/sauvegarde.txt", "r");
    if (lire_points == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        exit(1);
    }

    int i = 0;
    while (i < taille_max) {
        int result = fscanf(lire_points, " %49s %d\n", joueur[i].nom, &joueur[i].score);

        // Si fscanf a échoué à lire les deux éléments, sortir de la boucle
        if (result != 2) {
            if (result == EOF) {
                // Fin du fichier, on arrête
                break;
            } else {
                // Problème de format, on peut afficher une erreur
                printf("Erreur de format dans le fichier de scores.\n");
                break;
            }
        }

        i++;
    }

    fclose(lire_points);
    return i; // Retourner le nombre de scores lus
}

int comparer_scores(const void *a, const void *b) {
    Joueur *j1 = (Joueur *)a;
    Joueur *j2 = (Joueur *)b;
    return j2->score - j1->score; // Tri décroissant
}


 void affichescore(SDL_Renderer *renderer) {
    // Charger la police
    TTF_Font *Font = TTF_OpenFont("../police/arialbd.ttf", 30);
    // Charger le fond d'écran


    // Lire et trier les scores
    Joueur joueurs[100];
    int nb_joueurs = lire_score(100, joueurs);

    if (nb_joueurs == 0) {
        printf("Aucun score à afficher.\n");
        TTF_CloseFont(Font);
        return;
    }

    qsort(joueurs, nb_joueurs, sizeof(Joueur), comparer_scores);

    // Limiter au top 10
    if (nb_joueurs > 10) {
        nb_joueurs = 10;
    }

    // Afficher les scores triés
    SDL_Color couleurBlanche = {255, 255, 255, 255};
    SDL_Rect TextRect;
    TextRect.x = 100; // Position de départ X
    TextRect.y = 100; // Position de départ Y
    TextRect.w = 0;   // Largeur sera ajustée automatiquement
    TextRect.h = 0;   // Hauteur sera ajustée automatiquement

    for (int i = 0; i < nb_joueurs; i++) {
        // Créer le texte pour chaque joueur
        char scoreTexte[100];
        snprintf(scoreTexte, sizeof(scoreTexte), "%d. %s : %d", i + 1, joueurs[i].nom, joueurs[i].score);

        SDL_Surface *TextSurface = TTF_RenderText_Blended_Wrapped(Font, scoreTexte, couleurBlanche, 800);


        SDL_Texture *TextTexture = SDL_CreateTextureFromSurface(renderer, TextSurface);


        // Ajuster la taille du rectangle à la taille du texte
        TextRect.w = TextSurface->w;
        TextRect.h = TextSurface->h;

        // Rendre la texture dans le renderer
        SDL_RenderCopy(renderer, TextTexture, NULL, &TextRect);

        // Libérer les ressources pour ce texte
        SDL_FreeSurface(TextSurface);
        SDL_DestroyTexture(TextTexture);

        // Passer à la ligne suivante
        TextRect.y += 50; // Ajuster l'espacement vertical entre les lignes
    }
    SDL_RenderPresent(renderer);
    TTF_CloseFont(Font);
}



