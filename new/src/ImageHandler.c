#include <SDL_image.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <stdio.h>
#include <windows.h>
#include "../header/ImageHandler.h"

SDL_Texture* AfficheImage (SDL_Renderer *renderer, char *path, int x, int y) {
    IMG_Init(IMG_INIT_JPG); //Charge la bibliothèque SDL_image pour pouvoir afficher des .jpg
    IMG_Init(IMG_INIT_PNG); //Charge la bibliothèque SDL_image pour pouvoir afficher des .png
    SDL_Texture *img = IMG_LoadTexture(renderer,path); //Charge une image et la transforme en texture
    SDL_Rect texr; //creer un rectanlge
    SDL_QueryTexture(img, NULL, NULL, &texr.w, &texr.h); //Associe la texture à un rectangle pour pouvoir la charger dans le renderer
    texr.x = x; //coordonnées x du rectangle
    texr.y = y; //coordonnées y du rectangle
    SDL_RenderCopy(renderer, img, NULL, &texr); //Envoie l'image dans le renderer, elle sera affiché à l'appelle de SDL_RenderPresent(renderer)
    return img;
}