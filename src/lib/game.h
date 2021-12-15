#ifndef GAME_H_
#define GAME_H_

#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "entity.h"
#include "level.h"
#include "api.h"
#include "ai.h"
#include "draw.h"

void game_charge(Levels** level);
void game_score(Entity** entity, Levels** level);
void game_kill(Entity*** entity, Levels** level, const int entity_len, const int pl_index, const int coop_pl_index);
void game_teleport(Entity** entity, Levels* level);
void game_win(SDL_Window* win, Levels** level, int* win_width, int* win_height);
void find_player(Entity*** entities, const int entities_len, Levels** level);

void change_window_size(SDL_Window* win, Levels** level, int* win_width, int* win_height);
void change_level(SDL_Window* win, Levels** level, int* win_width, int* win_height);

void game_run(SDL_Renderer** ren, Levels** level, const int animation_count, const int animation_freq, const int pl_index, const int coop_pl_index, const int scale, const int move_scale, const int debug);
void game_restart(SDL_Window* win, SDL_Renderer** ren, Levels** level, int* pl_index, int* win_width, int* win_height, const int levels_count, const int coop, const int debug);

void load_texture(SDL_Renderer** ren, Levels** levels, int debug);
void load_levels(Levels** levels, const int levels_count, const int coop, const int debug);

#endif