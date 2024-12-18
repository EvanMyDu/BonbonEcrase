#include <SDL_image.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <stdio.h>
#include <windows.h>
#include "../header/ImageHandler.h"

SDL_Texture* AfficheImage (SDL_Renderer *renderer, char *path, int x, int y) {
    IMG_Init(IMG_INIT_JPG);
    IMG_Init(IMG_INIT_PNG);
    SDL_Texture *img = IMG_LoadTexture(renderer,path);
    SDL_Rect texr;
    SDL_QueryTexture(img, NULL, NULL, &texr.w, &texr.h);
    texr.x = x;
    texr.y = y;
    SDL_RenderCopy(renderer, img, NULL, &texr);
    return img;
}