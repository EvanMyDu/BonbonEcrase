#ifndef BUTTON_H
#define BUTTON_H

extern SDL_Rect buttons_game[78];
extern int couleur_boutons[78];
extern int largeur_grille;
extern int hauteur_grille;
extern int clicked;
extern int indice_clicked;

void enregistrer_boutton(SDL_Rect tab[], SDL_Rect rect, int rang);
void CreerBoutonMenu(SDL_Renderer* renderer, int x, int y, int width, int height, int numero);
void CreerBoutonJeu(SDL_Renderer* renderer, int x, int y, int width, int height, int numero);
void creer_grille(SDL_Renderer* renderer, int gamemode);
void remonter_couleur();
void ajouter_ligne();
int MouseInRect(SDL_Rect rect);
int GetButtonPurposeMenu(SDL_Renderer *renderer, int rang_d, int rang_f, int state);
void GetButtonPurposeGame(SDL_Renderer *renderer);
int CheckAllRectMenu();
int CheckAllRectGame();
int choix_couleur();
#endif //BUTTON_H
