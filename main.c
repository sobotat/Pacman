/**
 * Docs: http://wiki.libsdl.org/FrontPage
 * Tutorial: http://lazyfoo.net/tutorials/SDL/index.php
 */

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include <stdlib.h>

#include "src/lib/sdl_playground.h"
#include "src/lib/draw.h"
#include "src/lib/entity.h"
#include "src/lib/level.h"
#include "src/lib/api.h"
#include "src/lib/ai.h"
#include "src/lib/game.h"


int main(int argc, char** argv) {
    int debug = 0, counter = 0, last_score = 0, last_lives = 0, last_win = 0, last_charge = 0, game_started = 0;

    //Settings    
    int win_width = 810, win_height = 505;
    int scale = 60, move_speed = 4, fps = 0; //, move_scale = scale/move_speed
    int animation_count = 0, animation_freq = scale/6/2;
    int levels_count = 3, coop = 0;

    //Args
    get_args( argc, argv, &coop, &move_speed, &levels_count, &debug);
    
    SDL_Window * win = NULL;
    SDL_Renderer * ren = NULL;
    SDL_Texture* score_texture = NULL; SDL_Texture* win_texture = NULL;

    bool initialized = sdl_playground_init( &win, &ren, win_width, win_height);

    if ( !initialized ){
        sdl_playground_destroy( win, ren );
        return -1;
    }
    
    // Load Level
    Levels* my_levels = NULL;
    load_levels(&my_levels, levels_count, coop, debug);
    printf("Level Loaded\n");

    // Find Player Location in Level
    find_player(&(my_levels->entities[my_levels->current_level]), my_levels->entities_len[my_levels->current_level], &my_levels);  
    if(my_levels->coop == 1)
        printf("Coop is enabled\n");

    // Setting window size
    change_window_size(win, &my_levels, &win_width, &win_height);

    // Texture load
    load_texture(&ren, &my_levels, debug);
    printf("Textures Loaded\n");  

    SDL_Event e;
    bool quit = false;
    SDL_PixelFormat * fmt;
    Uint32 format = SDL_GetWindowPixelFormat(win);
    fmt = SDL_AllocFormat(format);

    printf("Starting game ...\n\n");
    while ( !quit ) {
        int tick_start_time = SDL_GetTicks();
        float render_start_time = SDL_GetPerformanceCounter();
        while ( SDL_PollEvent( &e ) ) {
            if ( e.type == SDL_QUIT ) {
                quit = true;
            }
            else if ( e.type == SDL_KEYDOWN ) { // key pressed down
                if ( e.key.keysym.sym == SDLK_r ) {
                    game_restart( win, &ren, &my_levels, &(my_levels->pl_index), &win_width, &win_height,levels_count, coop, debug);
                }else if(e.key.keysym.sym == SDLK_SPACE){
                    if (my_levels->game_win == 0)                                
                        my_levels->game_running = 1;
                }else if(e.key.keysym.sym == SDLK_ESCAPE){
                    my_levels->game_running = 0;
                }else if(e.key.keysym.sym == SDLK_l){
                    change_level( win,&my_levels, &win_width, &win_height);
                }

                if( e.key.keysym.sym == SDLK_LEFT ){
                    my_levels->entities[my_levels->current_level][my_levels->pl_index]->direction_wanted = 0;
                    if (my_levels->game_win == 0)                    
                        my_levels->game_running = 1;
                }else if( e.key.keysym.sym == SDLK_RIGHT ){
                    my_levels->entities[my_levels->current_level][my_levels->pl_index]->direction_wanted = 1;
                    if (my_levels->game_win == 0)                     
                        my_levels->game_running = 1;
                }else if( e.key.keysym.sym == SDLK_UP ){
                    my_levels->entities[my_levels->current_level][my_levels->pl_index]->direction_wanted = 2;
                    if (my_levels->game_win == 0)                     
                        my_levels->game_running = 1;
                }else if( e.key.keysym.sym == SDLK_DOWN ){
                    my_levels->entities[my_levels->current_level][my_levels->pl_index]->direction_wanted = 3;
                    if (my_levels->game_win == 0)                     
                        my_levels->game_running = 1;
                }else if( e.key.keysym.sym == SDLK_a && my_levels->coop_pl_index != -1 && my_levels->coop == 1){
                    my_levels->entities[my_levels->current_level][ my_levels->coop_pl_index]->direction_wanted = 0;
                    if (my_levels->game_win == 0)                     
                        my_levels->game_running = 1;
                }else if( e.key.keysym.sym == SDLK_d &&  my_levels->coop_pl_index != -1 && my_levels->coop == 1 ){
                    my_levels->entities[my_levels->current_level][ my_levels->coop_pl_index]->direction_wanted = 1;
                    if (my_levels->game_win == 0)                     
                        my_levels->game_running = 1;
                }else if( e.key.keysym.sym == SDLK_w &&  my_levels->coop_pl_index != -1 && my_levels->coop == 1 ){
                    my_levels->entities[my_levels->current_level][ my_levels->coop_pl_index]->direction_wanted = 2;
                    if (my_levels->game_win == 0)                     
                        my_levels->game_running = 1;
                }else if( e.key.keysym.sym == SDLK_s &&  my_levels->coop_pl_index != -1 && my_levels->coop == 1 ){
                    my_levels->entities[my_levels->current_level][ my_levels->coop_pl_index]->direction_wanted = 3;
                    if (my_levels->game_win == 0)                     
                        my_levels->game_running = 1;
                }
            }
            else if (e.type == SDL_MOUSEBUTTONUP && e.button.button == SDL_BUTTON_LEFT) { // mouse button released
                // x: e.button.button.x
                // y: e.button.button.y
            }else if (e.type == SDL_MOUSEBUTTONDOWN){
                // if(e.button.button == SDL_BUTTON_RIGHT){}
            }else if (e.type == SDL_MOUSEMOTION) { // mouse movement
                // x: e.motion.x
                // y: e.motion.y
            }
        }

        SDL_RenderClear(ren);
        draw_background(&ren, win_width, win_height);
        draw_level(&ren, my_levels->entities[my_levels->current_level], my_levels->entities_len[my_levels->current_level], &my_levels, win_width, 1);

        if(my_levels->game_running == 1){
            game_run( &ren, &my_levels, animation_count, animation_freq, my_levels->pl_index , my_levels->coop_pl_index, scale, move_speed, debug);
        }

        if(counter >= 2 * scale || my_levels->score != last_score || my_levels->lives != last_lives || my_levels->charge_time != last_charge || my_levels->game_win != last_win){
            draw_hud(&ren, &score_texture, &win_texture, my_levels, win_width, 1);

            if(last_win == my_levels->game_win && my_levels->game_win == 1 && counter >= 2*scale){
                if (my_levels->current_level != my_levels->maps_len - 1){
                    game_win(win, &my_levels, &win_width, &win_height);    
                }
                counter = 0;
            }
            if(last_win != my_levels->game_win && my_levels->game_win != 0)
                my_levels->game_running = 0;
            
            last_win = my_levels->game_win;
            last_score = my_levels->score;
            last_lives = my_levels->lives;
            last_charge = my_levels->charge_time;
            if((last_win == my_levels->game_win && my_levels->game_win != 1))
                counter = 0;
            if(debug != 1){
                printf("\e[1;1H\e[2J");
                printf("Info:\n");
                printf(" Score: %i\n Lives: %i\n Charge %i\n FPS: %i\n\n", my_levels->score, my_levels->lives, my_levels->charge_time, fps);
            }else
                printf(" Score: %i\t Lives: %i\t Charge %i\t FPS: %i\n", my_levels->score, my_levels->lives, my_levels->charge_time, fps);
        }else{
            draw_hud(&ren, &score_texture, &win_texture, my_levels, win_width, 0);
            counter++;
        }
        
        SDL_RenderPresent(ren);   
        
        if(animation_count >= animation_freq)
            animation_count = 0;
        else
            animation_count++;

        float elapsed = (SDL_GetPerformanceCounter() - render_start_time) / (float)SDL_GetPerformanceFrequency();
        fps = (int)(1.0/elapsed); //move_scale = scale/move_speed; animation_freq = scale/6/2;        
        SDL_Delay((1000 - ((SDL_GetTicks() - tick_start_time) / 1000.0f))/ scale);
    }
    printf("Turning game off ...\n");

    levels_free(&my_levels);

    SDL_DestroyTexture(score_texture);
    SDL_DestroyTexture(win_texture);
    //SDL_DestroyTexture(texture);
    SDL_FreeFormat(fmt);
    sdl_playground_destroy( win, ren );

    return 0;
}
