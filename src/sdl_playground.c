#include "lib/sdl_playground.h"


bool sdl_playground_init( SDL_Window ** win, SDL_Renderer ** renderer, const int window_width, const int window_height ) {
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER)) {
        fprintf(stderr, "SDL_Init Error: %s\n", SDL_GetError());
        return false;
    }

    if(TTF_Init() != 0) {
        printf("TTF_Init: %s\n", SDL_GetError());
        return false;
    }

    *win = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_SHOWN);
    if (!win) {
        fprintf(stderr, "SDL_CreateWindow Error: %s\n", SDL_GetError());
        SDL_Quit();
        return false;
    }

    *renderer = SDL_CreateRenderer(*win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if ( !renderer ) {
        SDL_DestroyWindow( *win );
        fprintf(stderr, "SDL_CreateRenderer Error: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    return true;
}

void sdl_playground_destroy( SDL_Window * win, SDL_Renderer * renderer ) {
    if ( renderer )  {
        SDL_DestroyRenderer( renderer );
        renderer = NULL;
    }

    if ( win )  {
        SDL_DestroyWindow( win );
        win = NULL;
    }

    SDL_Quit();
}