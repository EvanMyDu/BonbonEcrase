#ifndef BUTTON_H
#define BUTTON_H
void enregistrer_boutton(SDL_Rect tab[], SDL_Rect rect, int rang);
void CreerBoutonMenu(SDL_Renderer* renderer, int x, int y, int width, int height, int numero);
void CreerBoutonJeu(SDL_Renderer* renderer, int x, int y, int width, int height, int numero);
int MouseInRect(SDL_Rect rect);
int GetButtonPurposeMenu(SDL_Renderer *renderer, int rang_d, int rang_f);
int GetButtonPurposeGame(SDL_Renderer *renderer, int rang_d, int rang_f);
int CheckAllRectMenu();
int CheckAllRectGame();
#endif //BUTTON_H
