#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <windows.h>
#include "../header/AfficheFenetre.h"

#include <SDL_image.h>

#include "../header/ImageHandler.h"
#include "../header/Button.h"

SDL_Renderer* AfficheFenetre() {
    SDL_Window *window = SDL_CreateWindow("Hello World", SDL_WINDOWPOS_UNDEFINED, 35, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN) - 30, SDL_WINDOW_OPENGL); //Creer une fenêtre de la taille de l'écran de l'utilisateur
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); //Creer un renderer pour pouvoir afficher des textures
    return renderer;
}

void ActualiserFenetreMenu(SDL_Renderer *renderer) {
    int xplay = GetSystemMetrics(SM_CXSCREEN)/2-147, yplay = GetSystemMetrics(SM_CYSCREEN)/2 -50; //Determine les coordonnées du bouton et de l'image en fonction de la taille de l'écran
    int xscore =GetSystemMetrics(SM_CXSCREEN)/2-147, yscore = GetSystemMetrics(SM_CYSCREEN)/2 +50;  //Determine les coordonnées du bouton et de l'image en fonction de la taille de l'écran
    int xquitter =GetSystemMetrics(SM_CXSCREEN)/2-144, yquitter = GetSystemMetrics(SM_CYSCREEN)/2 + 150; //Determine les coordonnées du bouton et de l'image en fonction de la taille de l'écran
    int xtitre = GetSystemMetrics(SM_CXSCREEN)/2-550, ytitre = 50; //Determine les coordonnées du bouton et de l'image en fonction de la taille de l'écran
    SDL_RenderClear(renderer); //Enlève les éléments afficher à l'instant t
    SDL_Texture *background = AfficheImage(renderer,"../image/background.png", 0, 0), *bouton = AfficheImage(renderer, "../image/playbouton.png",xplay ,yplay), *titre = AfficheImage(renderer, "../image/titre.png",xtitre ,ytitre), *scorebouton = AfficheImage(renderer, "../image/scorebouton.png", xscore, yscore), *quitter = AfficheImage(renderer, "../image/quitterbouton.png", xquitter, yquitter);
    //Charge les images qui seront affichées  sur le menu
    CreerBoutonMenu(renderer, xplay, yplay,294, 84, 0);
    CreerBoutonMenu(renderer, xplay, yscore,294, 84, 1);
    CreerBoutonMenu(renderer, xquitter, yquitter,294, 84, 2);
    SDL_RenderPresent(renderer); //Affiche les images chargées dans le renderer
    SDL_DestroyTexture(bouton); //Libère la mémoire en detruisant la texture
    SDL_DestroyTexture(background); //Libère la mémoire en detruisant la texture
    SDL_DestroyTexture(titre); //Libère la mémoire en detruisant la texture
    SDL_DestroyTexture(quitter); //Libère la mémoire en detruisant la texture
    SDL_DestroyTexture(scorebouton); //Libère la mémoire en detruisant la texture
}

void ActualiserFenetreChoixMode(SDL_Renderer *renderer) {
    int xrush = GetSystemMetrics(SM_CXSCREEN)/2-147, yrush = GetSystemMetrics(SM_CYSCREEN)/2 +50; //Determine les coordonnées du bouton et de l'image en fonction de la taille de l'écran
    int xpuzzle =GetSystemMetrics(SM_CXSCREEN)/2-147, ypuzzle = GetSystemMetrics(SM_CYSCREEN)/2 +200;  //Determine les coordonnées du bouton et de l'image en fonction de la taille de l'écran
    int xtitremode = GetSystemMetrics(SM_CXSCREEN)/2-550, ytitremode = 50; //Determine les coordonnées du bouton et de l'image en fonction de la taille de l'écran
    SDL_RenderClear(renderer);
    SDL_Texture *background = AfficheImage(renderer, "../image/background.png",0 ,0), *boutonrush = AfficheImage(renderer, "../image/rushbutton.png", xrush, yrush), *boutonpuzzle = AfficheImage(renderer,"../image/puzzlebuttton.png", xpuzzle, ypuzzle), *choixtitre = AfficheImage(renderer,"../image/modedejeu.png", xtitremode, ytitremode);
    CreerBoutonMenu(renderer, xrush, yrush, 294, 84, 3);
    CreerBoutonMenu(renderer, xpuzzle, ypuzzle,294, 84, 4);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(background);
    SDL_DestroyTexture(boutonrush);
    SDL_DestroyTexture(choixtitre);
    SDL_DestroyTexture(boutonpuzzle);
}

void ActualiserFenetreChoixGrille(SDL_Renderer *renderer) {
    char str[30]; // Taille suffisante pour contenir "../image/XX.png"
    int a = 110, b = 90; // Position initiale des boutons
    SDL_RenderClear(renderer); // Enlève les éléments affichés à l'instant t
    SDL_Texture *background = AfficheImage(renderer, "../image/background.png", 0, 0);

    for (int i = 0; i < 15; i++) {
        sprintf(str, "../image/%d.png", i);
        if (i % 5 == 0 && i != 0) {
            a = 110;
            b += 300;
        } else if (i % 5 != 0) {
            a += 340;
        }
        SDL_Texture *grille = AfficheImage(renderer, str, a, b);
        SDL_DestroyTexture(grille);
    }

    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(background);
}


void ActualiserFenetreJeu(SDL_Renderer *renderer) {
    SDL_RenderClear(renderer);
    SDL_Texture *adlaurent = AfficheImage(renderer, "../image/adlaurent.jpg",600 ,435);
    SDL_RenderPresent(renderer);
    SDL_DestroyTexture(adlaurent);
}