#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <SDL.h>
#include <windows.h>
#include "header/AfficheFenetre.h"


void main(int argc, char* argv[]) {
    int x, y;
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
            if (event.type == SDL_MOUSEMOTION) {
                x = event.motion.x;
                y = event.motion.y;

            }
        }
        printf("x = %d, y = %d\n", x, y);
        ActualiserFenetreMenu(renderer);
    }
    SDL_Quit();
}
