#include "lib/level.h"

Levels* levels_new( const int maps_len, const int textures_len, const int fonts_len){
    Levels* level = (Levels*) malloc(sizeof(Levels));

    level->maps = malloc(sizeof(char*) * maps_len * 50 * 50);
    level->maps_size_x = malloc(sizeof(int) * maps_len);
    level->maps_size_y = malloc(sizeof(int) * maps_len);
    level->maps_len = maps_len;
    level->current_level = 0;

    level->entities = malloc(sizeof(Entity***) * 10 * maps_len);
    level->entities_len = malloc(sizeof(int) * maps_len);
    for (int i = 0; i < maps_len; i++){
        level->entities[i] = malloc(sizeof(Entity**) * 10);
        level->entities_len[i] = 0;
        level->maps_size_x[i] = 0;
        level->maps_size_y[i] = 0;
    }

    level->textures = (SDL_Texture**)malloc(sizeof(SDL_Texture*) * textures_len);
    level->textures_len = textures_len;
    level->fonts = (TTF_Font**)malloc(sizeof(TTF_Font*) * fonts_len);
    level->fonts_len = fonts_len;
    
    level->score = 0;
    level->lives = 3;
    level->charge_time = 0;
    level->charge_start_time = 0;
    level->charge_count = 3;

    level->game_running = 0;
    level->game_win = 0;
}

void levels_free(Levels** level){
    for (int lc = 0; lc < (*level)->maps_len; lc++){
        for (int e = 0; e < (*level)->entities_len[lc]; e++){
            for (int t = 0; t < (*level)->entities[lc][e]->textures_len; t++){
                SDL_DestroyTexture((*level)->entities[lc][e]->textures[t]);    
            }
            free((*level)->entities[lc][e]->textures);
            free((*level)->entities[lc][e]);
        }
        free((*level)->entities[lc]);
        free((*level)->maps[lc]);
    }
    free((*level)->entities);
    free((*level)->entities_len);

    for (int t = 0; t < (*level)->textures_len; t++){
        SDL_DestroyTexture((*level)->textures[t]);
    }

    for (int f = 0; f < (*level)->fonts_len; f++){
        TTF_CloseFont((*level)->fonts[f]);
    }
    free((*level)->fonts);

    free((*level)->maps);
    free((*level)->maps_size_x);
    free((*level)->maps_size_y);
    free((*level)->textures);
    free((*level));
    (*level) = NULL;
}