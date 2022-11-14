/*//////////////////////////////////////////////////////////////////////////////
                          Handmade Ping-Pong
//////////////////////////////////////////////////////////////////////////////*/

#include "SDL2/SDL.h"
#include <stdio.h>

int main() {
    printf("Handmade Ping-Pong\n");

    if (SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("SDL Init failed.\n");
        SDL_GetError();
        return -1;
    }
    printf("SDL Init succeeded.\n");

    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    if (SDL_CreateWindowAndRenderer(800, 600, 0, &window, &renderer) < 0){
        printf("[ERROR] CreateWindowAndRenderer() failed.");
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    uint32_t ticks = 0;
    SDL_Event event;
    bool should_quit = false;
    const uint8_t* key_state = nullptr;

    SDL_Rect left_paddle, right_paddle;
    SDL_Rect ball;

    while (!should_quit){
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                should_quit = true;
            }
        }
        
        ticks = SDL_GetTicks();
        key_state = SDL_GetKeyboardState(NULL);
        if (key_state[SDL_SCANCODE_ESCAPE]) should_quit = true;
        if (key_state[SDL_SCANCODE_UP]);
        if (key_state[SDL_SCANCODE_DOWN]);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}