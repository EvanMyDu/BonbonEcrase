#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <SDL.h>
#include <windows.h>
#include "header/AfficheFenetre.h"


int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Renderer *renderer;
    SDL_bool run = SDL_TRUE;
    renderer = AfficheFenetre();
    while(run){
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
            {
                run = SDL_FALSE;
            }
        }
        ActualiserFenetreMenu(renderer);
    }
    SDL_Quit();
    return 0;
}
