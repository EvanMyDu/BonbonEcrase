
#ifndef SCORE_H
#define SCORE_H
typedef struct {
    char nom[50]; // Nom du joueur (max 49 caractères + '\0')
    int score;    // Score du joueur
} Joueur;
void sauvegarder_score(int score, char nom[]);
void afficher_scores(Joueur joueurs[], int nb_joueurs);
void traiter_scores();
int comparer_scores(const void *a, const void *b);
int lire_score(int taille_max, Joueur joueur[]);


#endif //SCORE_H
