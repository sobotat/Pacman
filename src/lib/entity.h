#ifndef ENTITY_H_
#define ENTITY_H_

#include <stdbool.h>
#include <SDL.h>
#include <SDL_ttf.h>

typedef struct{
    double pos_x;           // Position in level X and Y
    double pos_y;
    double start_pos_x;     // Position in level where entity spawns
    double start_pos_y;
    int last_change_x;      // Change of direction X and Y
    int last_change_y;
    char type;              // Character
    int style;              // Animation 0,1
    int direction;          // -1 stop, 0 left, 1 right, 2 up, 3 down  
    int direction_next;     // Next direction
    int direction_wanted;   // Wanted direction (Only for player)
    SDL_Texture** textures; // Arr of textures of entity
    int textures_len;       // Size of arr of textures||
    
} Entity;

Entity* entity_new(const double pos_x, const double pos_y, const char type);
void entity_swap_style(Entity** self);

#endif