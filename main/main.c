#include <stdio.h>
#include <SDL.h>




int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("Hello World", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 600, 800, SDL_WINDOW_OPENGL);
    SDL_Delay(5000);
    SDL_Quit();
    return 0;
}
