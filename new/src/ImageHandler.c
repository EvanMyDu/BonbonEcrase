#include <SDL_image.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <stdio.h>
#include <windows.h>
#include "../header/ImageHandler.h"

void AfficherImage (SDL_Renderer *renderer, char *path, int x, int y) {
    IMG_Init(IMG_INIT_JPG);
    SDL_Texture *img = IMG_LoadTexture(renderer,path);
    SDL_Rect texr;
    SDL_QueryTexture(img, NULL, NULL, &texr.w, &texr.h);
    texr.x = (GetSystemMetrics(SM_CXSCREEN) - texr.w) / 2;
    texr.y = (GetSystemMetrics(SM_CYSCREEN) - texr.h) / 2;
    SDL_RenderCopy(renderer, img, NULL, &texr);
}