#include "lib/game.h"

void game_charge(Levels** level){
    if( (*level)->charge_start_time != 0 && (int)(7500 - (SDL_GetTicks() - (*level)->charge_start_time)) <= 0){
        (*level)->charge_time = 0;
        (*level)->charge_start_time = 0;
    }
}
void game_score(Entity** entity, Levels** level){
    char item = (*level)->maps[(*level)->current_level][to_1d(round((*entity)->pos_x), round((*entity)->pos_y), (*level)->maps_size_y[(*level)->current_level])];
    if((*entity)->type == 'p'){
        if( 'o' == item){
            (*level)->charge_time = 1;
            (*level)->charge_count--;
            (*level)->charge_start_time = SDL_GetTicks();
            (*level)->maps[(*level)->current_level][to_1d(round((*entity)->pos_x), round((*entity)->pos_y), (*level)->maps_size_y[(*level)->current_level])] = ' ';
        }
        game_charge(level);
    }
    if((*level)->coop == 0){
        if( '.' == item){
            (*level)->score += 10;
            (*level)->maps[(*level)->current_level][to_1d(round((*entity)->pos_x), round((*entity)->pos_y), (*level)->maps_size_y[(*level)->current_level])] = ' ';
        }
    }else {
        if( '.' == item){
            if((*level)->entities[(*level)->current_level][(*level)->coop_pl_index[(*level)->current_level]]->pos_x == (*entity)->pos_x && 
               (*level)->entities[(*level)->current_level][(*level)->coop_pl_index[(*level)->current_level]]->pos_y == (*entity)->pos_y ){
                (*level)->coop_score += 10;
            }else{
                (*level)->score += 10;
            }
            (*level)->maps[(*level)->current_level][to_1d(round((*entity)->pos_x), round((*entity)->pos_y), (*level)->maps_size_y[(*level)->current_level])] = ' ';
        }
    }
}
void game_kill(Entity*** entity, Levels** level, const int entity_len, const int pl_index, const int coop_pl_index){
    Entity* player = (*entity)[pl_index];
    Entity* coop_player = NULL;
    if((*level)->coop != 0)
        coop_player = (*entity)[coop_pl_index];
    
    for (int e = 0; e < entity_len; e++){
        if (e != pl_index && e != coop_pl_index){
            if( (*level)->coop == 0 && ((int)round((*entity)[e]->pos_x) == (int)round(player->pos_x)) && ((int)round((*entity)[e]->pos_y) == (int)round(player->pos_y)) ){
                
                if((*level)->charge_time == 1){   
                    (*entity)[e]->pos_x = (*entity)[e]->start_pos_x;
                    (*entity)[e]->pos_y = (*entity)[e]->start_pos_y;

                    if((*level)->charge_count == 3)
                        (*level)->score += 200;
                    else if((*level)->charge_count == 2)
                        (*level)->score += 400;
                    else if((*level)->charge_count == 1)
                        (*level)->score += 800;
                    else if((*level)->charge_count == 0)
                        (*level)->score += 1600;
                }else{
                    (*level)->lives--;
                    player->direction = -1;
                    (*level)->game_running = 0;
                    
                    if((*level)->lives == 0){
                        (*level)->game_running = 0;
                        (*level)->game_win = -1;
                    }else{
                        for (int x = 0; x < entity_len; x++){
                            (*entity)[x]->pos_x = (*entity)[x]->start_pos_x;
                            (*entity)[x]->pos_y = (*entity)[x]->start_pos_y;
                        }
                    }
                }
            }
            else if((*level)->coop != 0){
                if( ((int)round((*entity)[e]->pos_x) == (int)round(player->pos_x)) && ((int)round((*entity)[e]->pos_y) == (int)round(player->pos_y)) || 
                    ((int)round((*entity)[e]->pos_x) == (int)round(coop_player->pos_x)) && ((int)round((*entity)[e]->pos_y) == (int)round(coop_player->pos_y)) ){
                    if((*level)->charge_time == 1){   
                        if( (int)round(coop_player->pos_x) == (int)round((*entity)[e]->pos_x) && 
                            (int)round(coop_player->pos_y) == (int)round((*entity)[e]->pos_y) ){
                            if((*level)->charge_count == 3)
                                (*level)->coop_score += 200;
                            else if((*level)->charge_count == 2)
                                (*level)->coop_score += 400;
                            else if((*level)->charge_count == 1)
                                (*level)->coop_score += 800;
                            else if((*level)->charge_count == 0)
                                (*level)->coop_score += 1600;
                        }else{
                            if((*level)->charge_count == 3)
                                (*level)->score += 200;
                            else if((*level)->charge_count == 2)
                                (*level)->score += 400;
                            else if((*level)->charge_count == 1)
                                (*level)->score += 800;
                            else if((*level)->charge_count == 0)
                                (*level)->score += 1600;
                        }

                        (*entity)[e]->pos_x = (*entity)[e]->start_pos_x;
                        (*entity)[e]->pos_y = (*entity)[e]->start_pos_y;
                    }else{
                        (*level)->lives--;
                        player->direction = -1;
                        if(coop_pl_index != -1)
                            coop_player->direction = -1;
                        (*level)->game_running = 0;
                        
                        if((*level)->lives == 0){
                            (*level)->game_running = 0;
                            (*level)->game_win = -1;
                        }else{
                            for (int x = 0; x < entity_len; x++){
                                (*entity)[x]->pos_x = (*entity)[x]->start_pos_x;
                                (*entity)[x]->pos_y = (*entity)[x]->start_pos_y;
                            }
                        }
                    }
                }
            }
        }
        
    }    
}
void game_teleport(Entity** entity, Levels* level){
    if((int)(*entity)->pos_x < level->maps_size_x[level->current_level] - 1.5){
        if(level->maps[level->current_level][to_1d((int)(*entity)->pos_x, (int)(*entity)->pos_y, level->maps_size_y[level->current_level])] == 't'){
            if((int)(*entity)->pos_x > level->maps_size_x[level->current_level]/2 && (*entity)->direction == 1){
                (*entity)->pos_x = 0.5;
                (*entity)->direction = 1;
            }else if((int)(*entity)->pos_x < level->maps_size_x[level->current_level]/2 && (*entity)->direction == 0){
                (*entity)->pos_x = level->maps_size_x[level->current_level] - 1.5;
                (*entity)->direction = 0;
            }else if( ((int)(*entity)->pos_x > level->maps_size_x[level->current_level]/2 && (*entity)->direction != 0) && 
                    ((int)(*entity)->pos_x < level->maps_size_x[level->current_level]/2 && (*entity)->direction != 1) ){
                fprintf(stderr ,"Error in game_teleport C-%c d%i\n", (*entity)->type, (*entity)->direction);
                fprintf(stderr ," x%i mx%i\n", (int)(*entity)->pos_x, level->maps_size_x[level->current_level]/2);
            }
        }
    }else{
        (*entity)->pos_x = 0.5;
        (*entity)->direction = 1;
    }
}
void game_win(SDL_Window* win, Levels** level, int* win_width, int* win_height, const double win_scale){
    (*level)->game_win = 0;
    (*level)->game_running = 1;
    (*level)->charge_time = 0; (*level)->charge_count = 3;
    change_level(win, level, win_width, win_height, win_scale);
}
void find_player(Levels** level){
    for (int m = 0; m < (*level)->maps_len; m++){    
        for (int i = 0; i < (*level)->entities_len[m]; i++){
            if((*level)->entities[m][i]->type == 'p'){
                if((*level)->pl_index[m] == -1)
                    (*level)->pl_index[m] = i;
                else
                    (*level)->coop_pl_index[m] = i;
            }
        }
        if((*level)->pl_index[m] == -1){
            fprintf(stderr, "Player not found in level\n");
            exit(1);
        }
        (*level)->entities[m][(*level)->pl_index[m]]->direction = -1;
        (*level)->entities[m][(*level)->pl_index[m]]->direction_next = -1;
        if((*level)->coop_pl_index[m] != -1){
            (*level)->entities[m][(*level)->coop_pl_index[m]]->direction = -1;
            (*level)->entities[m][(*level)->coop_pl_index[m]]->direction_next = -1;
        }
    }
}


void change_window_size(SDL_Window* win, Levels** level, int* win_width, int* win_height, const double win_scale){
    *win_width = 60 + (((*level)->maps_size_x[(*level)->current_level] * 30)) * win_scale;
    *win_height = 125 + (((*level)->maps_size_y[(*level)->current_level] * 30)) * win_scale;
    SDL_SetWindowSize(win, *win_width, *win_height);
    SDL_SetWindowPosition(win, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}
void change_level(SDL_Window* win, Levels** level, int* win_width, int* win_height, const double win_scale){

    for (int e = 0; e < (*level)->entities_len[(*level)->current_level]; e++){
        (*level)->entities[(*level)->current_level][e]->pos_x = (*level)->entities[(*level)->current_level][e]->start_pos_x;
        (*level)->entities[(*level)->current_level][e]->pos_y = (*level)->entities[(*level)->current_level][e]->start_pos_y;
    }    
    
    if((*level)->current_level != (*level)->maps_len - 1)
        (*level)->current_level++;
    else
        (*level)->current_level = 0;

    
    change_window_size(win, level, win_width, win_height, win_scale);
}

void game_run(SDL_Renderer** ren, Levels** level, const int animation_count, const int animation_freq, const int pl_index, const int coop_pl_index, const int scale, const int move_scale, const double win_scale, const int debug){
    for (int i = 0; i < (*level)->entities_len[(*level)->current_level]; i++){
        Entity* entity = (*level)->entities[(*level)->current_level][i];
        int entity_pos_x = (int)round(entity->pos_x);
        int entity_pos_y = (int)round(entity->pos_y);

        char to_left = (*level)->maps[(*level)->current_level][to_1d(entity_pos_x - 1, entity_pos_y, (*level)->maps_size_y[(*level)->current_level])];
        char to_right = (*level)->maps[(*level)->current_level][to_1d(entity_pos_x + 1, entity_pos_y, (*level)->maps_size_y[(*level)->current_level])];
        char to_up = (*level)->maps[(*level)->current_level][to_1d(entity_pos_x, entity_pos_y - 1, (*level)->maps_size_y[(*level)->current_level])];
        char to_down = (*level)->maps[(*level)->current_level][to_1d(entity_pos_x, entity_pos_y + 1, (*level)->maps_size_y[(*level)->current_level])];

        
        if(entity->direction == -1 && entity->type == 'p'){
            entity->pos_x = entity_pos_x;
            entity->pos_y = entity_pos_y;
            if(animation_count == animation_freq)
                entity_swap_style(&entity);
            choose_way( &entity, level, to_left, to_right, to_up, to_down);
        }else if(entity->direction == 0){
            choose_way( &entity, level, to_left, to_right, to_up, to_down);
            go_left( &entity, (*level), to_left, to_right, to_up, to_down, scale, move_scale, animation_count, animation_freq);
        }else if(entity->direction == 1){
            choose_way( &entity, level, to_left, to_right, to_up, to_down);
            go_right(&entity, (*level), to_left, to_right, to_up, to_down, scale, move_scale, animation_count, animation_freq);
        }else if(entity->direction == 2){
            choose_way( &entity, level, to_left, to_right, to_up, to_down);
            go_up(&entity, (*level), to_left, to_right, to_up, to_down, scale, move_scale, animation_count, animation_freq);
        }else if(entity->direction == 3){
            choose_way( &entity, level, to_left, to_right, to_up, to_down);
            go_down(&entity, (*level), to_left, to_right, to_up, to_down, scale, move_scale, animation_count, animation_freq);
        }

        if(debug == 1){
            if(entity->type == 'r'){
                draw_debug(ren, entity, 255, 0, 0, win_scale);
            }else if(entity->type == 'c'){
                draw_debug(ren, entity, 0, 128, 255, win_scale);
            }else if(entity->type == 'm'){
                draw_debug(ren, entity, 255, 0, 128, win_scale);
            }else if(entity->type == 'y'){
                draw_debug(ren, entity, 255, 128, 0, win_scale);
            }else if(entity->type == 'p'){
                draw_debug(ren, entity, 200, 200, 200, win_scale);
            }
        }
    }

    game_kill(&((*level)->entities[(*level)->current_level]), &(*level), (*level)->entities_len[(*level)->current_level], pl_index, coop_pl_index);
}
void game_restart(SDL_Window* win, SDL_Renderer** ren, Levels** level, int* pl_index, int* win_width, int* win_height, const double win_scale, const int levels_count, const int coop, const int debug){
    printf("Restarting Game ...\n");
    levels_free( level);
    load_levels( level, levels_count, coop, debug);
    find_player( level);
    load_texture( ren, level, debug);
    change_window_size(win, level, win_width, win_height, win_scale);
    printf("Restart Complete\n");
}

void load_texture(SDL_Renderer** ren, Levels** levels, int debug){
    (*levels)->fonts[0] = TTF_OpenFont("res/fonts/BebasNeue-Regular.ttf", 128);
    (*levels)->fonts[1] = TTF_OpenFont("res/fonts/Orbitron-ExtraBold.ttf", 400);
    check_font_error((*levels)->fonts[0]); check_font_error((*levels)->fonts[1]);

    (*levels)->textures[0] = SDL_CreateTextureFromSurface( *ren, IMG_Load("res/charge.png"));
    (*levels)->textures[1] = SDL_CreateTextureFromSurface( *ren, IMG_Load("res/life1.png"));
    (*levels)->textures[2] = SDL_CreateTextureFromSurface( *ren, IMG_Load("res/life2.png"));
    (*levels)->textures[3] = SDL_CreateTextureFromSurface( *ren, IMG_Load("res/teleport1.png"));
    (*levels)->textures[4] = SDL_CreateTextureFromSurface( *ren, IMG_Load("res/teleport2.png"));
    check_texture_error((*levels)->textures[0]); check_texture_error((*levels)->textures[1]);
    check_texture_error((*levels)->textures[2]); check_texture_error((*levels)->textures[3]);
    check_texture_error((*levels)->textures[4]);

    // Walls
    (*levels)->textures[5] = SDL_CreateTextureFromSurface( *ren, IMG_Load("res/walls/wall_straight.png"));
    (*levels)->textures[6] = SDL_CreateTextureFromSurface( *ren, IMG_Load("res/walls/wall_curve.png"));
    (*levels)->textures[7] = SDL_CreateTextureFromSurface( *ren, IMG_Load("res/walls/wall_tcross.png"));
    (*levels)->textures[8] = SDL_CreateTextureFromSurface( *ren, IMG_Load("res/walls/wall_cross.png"));
    (*levels)->textures[9] = SDL_CreateTextureFromSurface( *ren, IMG_Load("res/walls/wall_end.png"));
    (*levels)->textures[10] = SDL_CreateTextureFromSurface( *ren, IMG_Load("res/walls/wall_point.png"));
    (*levels)->textures[11] = SDL_CreateTextureFromSurface( *ren, IMG_Load("res/walls/wall_doors.png"));
    check_texture_error((*levels)->textures[5]); check_texture_error((*levels)->textures[6]);
    check_texture_error((*levels)->textures[7]); check_texture_error((*levels)->textures[8]);
    check_texture_error((*levels)->textures[9]); check_texture_error((*levels)->textures[10]); 
    check_texture_error((*levels)->textures[11]); 

    for (int lc = 0; lc < (*levels)->maps_len; lc++){
        for (int e = 0; e < (*levels)->entities_len[lc]; e++){

            int style = 0;
            int size = 12, direction = 0;
            if((*levels)->entities[lc][e]->type == 'p')
                size = 10, direction = -1;

            for (int s = 0, d = direction; s < size; s = s + 2, d++){
                style = 0;
                char* address_1 = get_address((*levels)->entities[lc][e], *levels, lc, d, style);
                (*levels)->entities[lc][e]->textures[s] = SDL_CreateTextureFromSurface( *ren, IMG_Load(address_1));
                check_texture_error((*levels)->entities[lc][e]->textures[s]);

                style = 1;
                char* address_2 = get_address((*levels)->entities[lc][e], *levels, lc, d, style);
                (*levels)->entities[lc][e]->textures[(s + 1)] = SDL_CreateTextureFromSurface( *ren, IMG_Load(address_2));
                check_texture_error((*levels)->entities[lc][e]->textures[(s + 1)]);

                if(debug == 1){
                    printf("%i %s\n", d, address_1);
                    printf("%i %s\n", d, address_2);
                }
                free(address_1); free(address_2);
                (*levels)->entities[lc][e]->textures_len++;
            }
        }
    }
}
void load_levels(Levels** levels, const int levels_count, const int coop, const int debug){
    (*levels) = levels_new( levels_count, 12, 2);
    (*levels)->coop = coop;
    
    for (int lc = 0; lc < levels_count; lc++){    
        char address[100]; address[0] = '\0'; strcat(address, "res/levels/level0"); 
        char str[10]; sprintf(str, "%i", lc + 1); strcat(address, str); strcat(address, ".txt\0");

        if(debug == 1)
            printf("%s\n", address);

        FILE* file = fopen(address, "r");
        if(!file){
            fprintf(stderr,"Level load: File Error\n");
            exit(1);       
        }
        
        fseek(file, 0L, SEEK_END);
        long int sz = ftell(file);
        rewind(file);

        int level_x, level_y; 
        fscanf(file ,"%i %i", &level_x, &level_y);
        
        (*levels)->maps_size_x[lc] = level_x;
        (*levels)->maps_size_y[lc] = level_y;

        char* level_map = malloc(sizeof(char) * (sz + 20));        
        for (int y = 0; y < (*levels)->maps_size_y[lc]; y++){
            for (int x = 0; x < (*levels)->maps_size_x[lc]; x++){
                char l;
                fscanf(file, "%c", &l);
                if(l == '\n' || l == 'c' || l == 'y' || l == 'm' || l == 'r' || l == 'p'){
                    if(l == '\n')
                        x--;
                    else{
                        level_map[to_1d(x, y, (*levels)->maps_size_y[lc])] = ' ';
                        (*levels)->entities[lc][(*levels)->entities_len[lc]] = entity_new(x , y, l);
                        
                        if(debug == 1)
                            printf("ls%i %c x%i y%i\n", lc, (*levels)->entities[lc][(*levels)->entities_len[lc]]->type, x, y);
                            
                        ((*levels)->entities_len[lc])++;
                    }
                }else{
                    level_map[to_1d(x, y, (*levels)->maps_size_y[lc])] = l;             
                }
            }        
        }

        level_map[((*levels)->maps_size_x[lc] * (*levels)->maps_size_y[lc])] = '\0';

        if(debug == 1){
            for (int y = 0; y < (*levels)->maps_size_y[lc]; y++){
                for (int x = 0; x < (*levels)->maps_size_x[lc]; x++){
                    printf("%c", level_map[to_1d(x,y, (*levels)->maps_size_y[lc])]);
                }
                printf("\n");
            }
        }
        
        fclose(file);
        (*levels)->maps[lc] = level_map;
    }
}