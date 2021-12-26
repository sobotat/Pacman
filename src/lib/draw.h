#ifndef DRAW_H_
#define DRAW_H_

#include <stdbool.h>
#include <SDL.h>
#include <SDL_ttf.h>

#include "level.h"
#include "entity.h"
#include "api.h"

void draw_start_screen(SDL_Renderer** ren, Levels* level, const int win_width, const int win_height, const int time, const int create_new);
void draw_finish_screen(SDL_Renderer** ren, SDL_Texture** texture_score, SDL_Texture** texture_win, SDL_Texture** texture_continue, Levels* level, const int win_width, const int win_height, const int time, const int create_new);

void draw_hud(SDL_Renderer** ren, SDL_Texture** texture_score, SDL_Texture** texture_win, Levels* level, const int win_width, const int create_new);
void draw_background(SDL_Renderer** ren ,const int win_width, const int win_height);
void draw_entity(SDL_Renderer** ren, Entity* entity, Levels* level);
void draw_level(SDL_Renderer** ren, Entity** entities, const int entities_len, Levels** level, const int win_width,const int scale);

void draw_debug(SDL_Renderer** ren, Entity* entity, const int red, const int green, const int blue);

#endif
