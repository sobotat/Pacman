#include "lib/api.h"

int to_1d( const int row, const int col, const int cols ) {
    return row * cols + col;
}

char* get_address(Entity* entity, Levels* level, const int level_index, const int direction, const int style){
    char* address = malloc(sizeof(char) * 100); address[0] = '\0';

    if(level->coop == 1 && entity->type == 'p')
        address = strcat(address, "res/characters/p/coop");
    else{
        address = strcat(address, "res/characters/");
    
        char type[2];
        if(direction == 4 || direction == 5){
            type[0] = 'g'; type[1] = '\0';
        }else{
            type[0] = entity->type; type[1] = '\0';
        }
        address = strcat(address, type);
    }

    if(entity->type != 'p')
        address = strcat(address, "/npc_");
    else{
        if(level->coop == 1){
            if( level->entities[level_index][level->coop_pl_index]->pos_x == entity->pos_x && 
                level->entities[level_index][level->coop_pl_index]->pos_y == entity->pos_y){
                address = strcat(address, "/coplayer_");
            }else
                address = strcat(address, "/player_");
        }else
            address = strcat(address, "/player_");
    }
    if(direction == -1)
        address = strcat(address, "stop");
    else if(direction == 0)
        address = strcat(address, "left");
    else if(direction == 1)
        address = strcat(address, "right");
    else if(direction == 2)
        address = strcat(address, "up");
    else if(direction == 3)
        address = strcat(address, "down");
    else if(direction == 4)
        address = strcat(address, "blue");
    else
        address = strcat(address, "white");

    char animation[2]; animation[0] = (style + 1) + '0'; animation[1] = '\0';
    address = strcat(address, animation);
    address = strcat(address, ".png");
    return address;
}

void get_args(int argc, char** argv, int* coop,int* move_speed, int* levels_count, int* debug){
    if(argc > 4){
        if(atoi(argv[argc - 4]) != 0)
            *coop = atoi(argv[argc - 4]);
        if(atoi(argv[argc - 3]) != 0)
            *move_speed = atoi(argv[argc - 3]);
        if(atoi(argv[argc - 2]) != 0)
            *levels_count = atoi(argv[argc - 2]);
        *debug = atoi(argv[argc - 1]);
    }else if(argc > 3){
        if(atoi(argv[argc - 3]) != 0)
            *coop = atoi(argv[argc - 3]);
        if(atoi(argv[argc - 2]) != 0)
            *move_speed = atoi(argv[argc - 2]);
        if(atoi(argv[argc - 1]) != 0)
            *levels_count = atoi(argv[argc - 1]);
    }else if (argc > 2){
        if(atoi(argv[argc - 2]) != 0)
            *coop = atoi(argv[argc - 2]);
        if(atoi(argv[argc - 1]) != 0)
            *move_speed = atoi(argv[argc - 1]);
    }else if (argc > 1){
        if(atoi(argv[argc - 1]) != 0)
            *coop = atoi(argv[argc - 1]);
    }
}

void check_texture_error(SDL_Texture* self){
    if(!self){
        fprintf(stderr, "Texture create error: %s\n", SDL_GetError());
        exit(1);
    }
}
void check_font_error(TTF_Font* self){
    if(!self){
        fprintf(stderr, "Font create error: %s\n", SDL_GetError());
        exit(1);
    }
}