/*//////////////////////////////////////////////////////////////////////////////
                          Handmade Ping-Pong
//////////////////////////////////////////////////////////////////////////////*/

#include "SDL2/SDL.h"
#include <stdio.h>

#define WINDOW_W 800
#define WINDOW_H 600

#define BALL_SIZE 20
#define BALL_SPEED 2

#define PAD_SPEED 5

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
    if (SDL_CreateWindowAndRenderer(WINDOW_W, WINDOW_H, 0, &window, &renderer) < 0){
        printf("[ERROR] CreateWindowAndRenderer() failed.");
    }

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    uint32_t ticks = 0;
    SDL_Event event;
    bool should_quit = false;
    const uint8_t* key_state = nullptr;

    SDL_Rect left_pad, right_pad;
    left_pad.x = 32;
    left_pad.h = WINDOW_H / 4;
    left_pad.y = (WINDOW_H / 4) - (left_pad.h / 2);
    left_pad.w = 12;
    right_pad = left_pad;
    right_pad.x = WINDOW_W - right_pad.w - 32;
    SDL_Rect ball;
    ball.w = BALL_SIZE;
    ball.h = BALL_SIZE;

    float velX = 0.0f, velY = 0.0f;
    uint32_t score = 0;
    bool turn = true;

    //serve
    left_pad.y = right_pad.y = (WINDOW_H/2)-(left_pad.h/2);
    if (turn){
        ball.x = left_pad.x + (left_pad.w * 4);
    }
    else {
        ball.x = right_pad.x - (right_pad.w * 4);
    }
    velX = -BALL_SPEED / 2;
    velY = 0.0f;
    ball.y = WINDOW_H / 2 - BALL_SIZE / 2;
    turn = !turn;

    while (!should_quit){
        while (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT){
                should_quit = true;
            }
        }
        
        ticks = SDL_GetTicks();
        key_state = SDL_GetKeyboardState(NULL);
        if (key_state[SDL_SCANCODE_ESCAPE]){
            should_quit = true;
        }
        if (key_state[SDL_SCANCODE_UP]){
            left_pad.y -= PAD_SPEED;
        }
        if (key_state[SDL_SCANCODE_DOWN]){
            left_pad.y += PAD_SPEED;
        }
        
        if (left_pad.y < 0){
            left_pad.y = 0;
        }
        else if (left_pad.y + left_pad.h > WINDOW_H){
            left_pad.y = WINDOW_H - left_pad.h;
        }
        if (right_pad.y < 0){
            right_pad.y = 0;
        }
        else if (right_pad.y + right_pad.h > WINDOW_H){
            right_pad.y = WINDOW_H - right_pad.h;
        }

        ball.x += velX;
        ball.y += velY;
        if (ball.x < 0 || ball.x > WINDOW_W) {
            ball.x = WINDOW_W / 2;
            ball.y = WINDOW_H / 2;
        }
        if (SDL_HasIntersection(&ball, &right_pad)){
            velX *= -1;
        }
        else if (SDL_HasIntersection(&ball, &left_pad)){
            velX *= -1;
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderFillRect(renderer, &left_pad);
        SDL_RenderFillRect(renderer, &right_pad);
        SDL_RenderFillRect(renderer, &ball);
        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}