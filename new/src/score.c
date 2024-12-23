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


void afficher_scores(Joueur joueurs[], int nb_joueurs) {
    for (int i = 0; i < nb_joueurs; i++) {
        printf("%s %d\n", joueurs[i].nom, joueurs[i].score);
    }
}
void traiter_scores() {
    Joueur joueurs[100]; // Tableau temporaire pour stocker tous les scores du fichier

    // Lire les scores depuis le fichier
    int nb_joueurs = lire_score(100, joueurs);

    // Vérifier si des scores ont été lus
    if (nb_joueurs == 0) {
        printf("Aucun score à afficher.\n");
        return;
    }

    // Trier les scores
    qsort(joueurs, nb_joueurs, sizeof(Joueur), comparer_scores);

    // Limiter au top 10
    if (nb_joueurs > 10) {
        nb_joueurs = 10;
    }

    // Afficher les scores triés
    afficher_scores(joueurs, nb_joueurs);
}

