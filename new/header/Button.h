

#ifndef BUTTON_H
#define BUTTON_H
void CreerBouton(SDL_Renderer* renderer, int x, int y, int width, int height, int numero);
int MouseInRect(SDL_Rect rect);
int CheckAllRect();
void enregistrer_bouttons(SDL_Rect tab[], SDL_Rect rect, int rang);
#endif //BUTTON_H
