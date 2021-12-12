#include "lib/entity.h"

Entity* entity_new(const double pos_x, const double pos_y, const char type){
    Entity * entity = (Entity *)malloc(sizeof(Entity));
    entity->pos_x = pos_x;
    entity->pos_y = pos_y;
    entity->start_pos_x = pos_x;
    entity->start_pos_y = pos_y;
    entity->last_change_x = -1;
    entity->last_change_y = -1;
    entity->type = type;
    entity->style = 0;
    entity->direction = 1;
    entity->direction_next = entity->direction;
    entity->direction_wanted = -1;
    entity->textures_len = 0;

    if(type != 'p'){
        entity->textures = (SDL_Texture**)malloc(sizeof(SDL_Texture*) * 12);
    }else{
        entity->textures = (SDL_Texture**)malloc(sizeof(SDL_Texture*) * 10);
    }

    return entity;
}

void entity_swap_style(Entity** self){
    if((*self)->style == 0)
        (*self)->style = 1;
    else
        (*self)->style = 0;
}

void find_player(Entity*** entities, const int entities_len, int* pl_index){
    for (int i = 0; i < entities_len; i++){
        if((*entities)[i]->type == 'p')
            *pl_index = i;
    }
    if(*pl_index == -1){
        fprintf(stderr, "Player not found in level\n");
        exit(1);
    }
    (*entities)[*pl_index]->direction = -1;
    (*entities)[*pl_index]->direction_next = -1;
}
