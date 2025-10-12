
//SDL libs
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//standard libs
#include <stdio.h>
#include <stdbool.h>

#define WINDOW_TITLE "HeimerDinger Simulation"
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

struct Simulation{
    SDL_Window *window;
    SDL_Renderer *renderer;
};

bool sdl_init(struct Simulation *sim){
    if(SDL_Init(SDL_INIT_EVERYTHING)){
        printf("Failed to initialize SDL libraries: %s\n", SDL_GetError());
        return true;
    };

    sim->window= SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!sim->window){
        printf("Error creating window: %s\n", SDL_GetError());
        return true;
    };

    sim -> renderer = SDL_CreateRenderer(sim->window, -1, 0);
    if (!sim->renderer){
        printf("Error creating renderer: %s\n", SDL_GetError());
        return true;
    };

    return false;
};

void sdl_cleanup(struct Simulation *sim){
    SDL_DestroyRenderer(sim->renderer);
    SDL_DestroyWindow(sim->window);
    SDL_Quit();
};

int main(int argc, char* args[]) {

    struct Simulation sim = {
        .window = NULL,
        .renderer = NULL,
    };



    if(sdl_init(&sim)){
        sdl_cleanup(&sim);
        exit(1);
    };

    SDL_RenderClear(sim.renderer);

    SDL_RenderPresent(sim.renderer);

    SDL_Delay(5000);


    sdl_cleanup(&sim);

    return 0;

}