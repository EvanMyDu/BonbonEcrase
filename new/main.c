#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <SDL.h>
#include <windows.h>
#include "header/AfficheFenetre.h"
#include "header/Game.h"

void main(int argc, char* argv[]) {
    game_loop();
}
