#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

int main(int argc, char* argv[]) {
    SDL_bool run = SDL_TRUE, maximized = SDL_TRUE;
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("Hello World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1920, 1040, SDL_WINDOW_SHOWN);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_Image* image = IMG_Load("image.png");
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
            SDL_SetRenderDrawColor(renderer, 100, 40, 40, 255);
            SDL_RenderClear(renderer);
            SDL_RenderPresent(renderer);
        }
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}


