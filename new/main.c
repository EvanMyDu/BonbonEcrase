#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <windows.h>

void AfficherImage (SDL_Renderer *renderer, char *path, int x, int y) {
    IMG_Init(IMG_INIT_JPG);
    SDL_Texture *img = IMG_LoadTexture(renderer,path);
    SDL_Rect texr;
    SDL_QueryTexture(img, NULL, NULL, &texr.w, &texr.h);
    texr.x = x;
    texr.y = y;
    SDL_RenderCopy(renderer, img, NULL, &texr);
}

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_bool run = SDL_TRUE;
    SDL_Window *window = SDL_CreateWindow("Hello World", SDL_WINDOWPOS_UNDEFINED, 35, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) - 30, SDL_WINDOW_OPENGL);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    while(run){
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
            {
                run = SDL_FALSE;
            }
        }
        SDL_RenderClear(renderer);

        AfficherImage(renderer,"../image/background.jpg", 0, 0);
        AfficherImage(renderer, "../image/BoutonRose.png",600 ,435);
        SDL_RenderPresent(renderer);
    }
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
