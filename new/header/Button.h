#ifndef BUTTON_H
#define BUTTON_H
void enregistrer_boutton(SDL_Rect tab[], SDL_Rect rect, int rang);
void CreerBoutonMenu(SDL_Renderer* renderer, int x, int y, int width, int height, int numero);
void CreerBoutonJeu(SDL_Renderer* renderer, int x, int y, int width, int height, int numero);
int MouseInRect(SDL_Rect rect);
void GetButtonPurposeMenu(int i, SDL_Renderer *renderer);
void GetButtonPurposeGame(int i, SDL_Renderer *renderer);
int CheckAllRectMenu();
int CheckAllRectGame();
#endif //BUTTON_H
