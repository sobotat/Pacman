#ifndef API_H_
#define API_H_

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include "entity.h"
#include "level.h"

int to_1d( const int row, const int col, const int cols );
char* get_address(Entity* entity, Levels* level, const int level_index, const int direction, const int style);

void get_args(int argc, char** argv, int* coop, int* move_speed, int* levels_count, int* debug);

void check_texture_error(SDL_Texture* self);
void check_font_error(TTF_Font* self);

#endif