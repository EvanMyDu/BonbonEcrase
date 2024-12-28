#ifndef GAME_H
#define GAME_H

extern int rang_suppression[100];

int SetGameMode(int a);
void creer_grille(SDL_Renderer* renderer, int gamemode);
void remonter_couleur();
void ajouter_ligne();
void echange_bonbon(int indice_echange);
void game_loop();

#endif //GAME_H
