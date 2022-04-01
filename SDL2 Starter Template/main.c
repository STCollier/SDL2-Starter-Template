#include <stdio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

//Prototype functions
int initialize();
void handle_input();

typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
    int input[256];
    bool running;
    bool close_requested;
    int resizable;
    int FPS;
    int width;
    int height;
    char title[30];
} Game;

Game game = {
    .input = {},
    .running = true,
    .close_requested = false,
    .resizable = false,
    .FPS = 60,
    .width = 1200,
    .height = 800,
    .title = "Window"
};

int main() {

    initialize();

    /*START OF GAME LOOP*/
    while(game.running && !game.close_requested) {

        SDL_SetRenderDrawColor(game.renderer, 181, 247, 255, 255);
        SDL_RenderClear(game.renderer);

        handle_input();

        //Update variables here

        SDL_RenderPresent(game.renderer);
        SDL_Delay(1000/game.FPS);

    }
    /*END OF GAME LOOP*/

    SDL_DestroyRenderer(game.renderer);
    SDL_DestroyWindow(game.window);
    SDL_Quit();

    return 0;
}

int initialize() {

    int canResize;

    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER) != 0) { //return 0 on success
        printf("error initializing SDL: %s\n", SDL_GetError());
        return 1;
    }

    if (game.resizable) {
        canResize = SDL_WINDOW_RESIZABLE;
    } else {
        canResize = 0;
    }

    game.window = SDL_CreateWindow(game.title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, game.width, game.height, canResize); //creates window
    if (!game.window) {
        printf("error creating window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    Uint32 render_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC; //creates a renderer
    game.renderer = SDL_CreateRenderer(game.window, -1, render_flags);
    if (!game.renderer) {
        printf("error creating renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(game.window);
        SDL_Quit();
        return 1;
    }
    return 0;
}

void handle_input() {

    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            game.close_requested = true;
            game.running = false;
        }

        if (event.type == SDL_KEYDOWN) {
            game.input[event.key.keysym.scancode] = true;
            //printf("True");
        }
        if (event.type == SDL_KEYUP) {
            game.input[event.key.keysym.scancode] = false;
            //printf("False");
        }
    }
}