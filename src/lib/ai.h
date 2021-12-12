#ifndef AI_H_
#define AI_H_

#include <stdlib.h>
#include "entity.h"
#include "level.h"
#include "game.h"

void go_left(Entity** entity, Levels* level, const char to_left, const char to_right, const char to_up, const char to_down, const int scale, const int move_speed, const int animation_count, const int animation_freq);
void go_right(Entity** entity, Levels* level, const char to_left, const char to_right, const char to_up, const char to_down, const int scale, const int move_speed, const int animation_count, const int animation_freq);
void go_up(Entity** entity, Levels* level, const char to_left, const char to_right, const char to_up, const char to_down, const int scale, const int move_speed, const int animation_count, const int animation_freq);
void go_down(Entity** entity, Levels* level,const char to_left, const char to_right, const char to_up, const char to_down, const int scale, const int move_speed, const int animation_count, const int animation_freq);

void choose_way_pom(Entity** entity, int way, char to_left, char to_right, char to_up, char to_down);
void choose_way(Entity** entity, Levels** level, char to_left, char to_right, char to_up, char to_down);

#endif