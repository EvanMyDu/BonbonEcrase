#include <stdio.h>
#include <SDL.h>

int main(int argc, char* argv[]) {
    SDL_bool run = SDL_TRUE, maximized = SDL_TRUE;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("Hello World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1040, SDL_WINDOW_SHOWN);
    while(run){
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch(event.type)
            {
                case SDL_QUIT:
                    run = SDL_FALSE;
                    break;
                default:
                    break;
            }
        }
    }
    SDL_Quit();
    return 0;
}


