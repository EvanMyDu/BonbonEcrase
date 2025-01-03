#include <SDL.h>
#ifndef SCORE_H
#define SCORE_H
typedef struct {
    char nom[50]; // Nom du joueur (max 49 caractères + '\0')
    int score;    // Score du joueur
} Joueur;
void sauvegarder_score(char nom[]);
void donner_points(int longueur_chaine, int consecutif);
int comparer_scores(const void *a, const void *b);
int lire_score(int taille_max, Joueur joueur[]);
void affichescore(SDL_Renderer *renderer);

#endif //SCORE_H
