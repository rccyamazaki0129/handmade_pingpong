#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include <stdio.h>

int main() {
    printf("Handmade Ping-Pong\n");
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
        printf("SDL Init failed.\n");
        SDL_GetError();
    }
    printf("SDL Init succeeded.\n");
    return 0;
}