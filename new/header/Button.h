#ifndef BUTTON_H
#define BUTTON_H

extern SDL_Rect buttons_game[72];
extern int couleur_boutons[72];
extern int largeur_grille;
extern int hauteur_grille;

void enregistrer_boutton(SDL_Rect tab[], SDL_Rect rect, int rang);
void CreerBoutonMenu(SDL_Renderer* renderer, int x, int y, int width, int height, int numero);
void CreerBoutonJeu(SDL_Renderer* renderer, int x, int y, int width, int height, int numero);
void creer_grille(SDL_Renderer* renderer, int gamemode);
void ajouter_ligne(SDL_Renderer *renderer);
int MouseInRect(SDL_Rect rect);
int GetButtonPurposeMenu(SDL_Renderer *renderer, int rang_d, int rang_f, int state);
int GetButtonPurposeGame(SDL_Renderer *renderer, int rang_d, int rang_f);
int CheckAllRectMenu();
int CheckAllRectGame();
int choix_couleur();
#endif //BUTTON_H
