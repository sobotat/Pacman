#include "lib/draw.h"

void draw_hud(SDL_Renderer** ren, SDL_Texture** texture_score, SDL_Texture** texture_win, Levels* level, const int win_width, const int create_new){
    SDL_Rect rect;

    // HP
    // Heart colors 75 150 142 / 50 135 125    
    for (int h = 0, x = win_width - 40; h < level->lives; h++, x -= 15){
        rect.x = x;
        rect.y = 20;
        rect.w = 20;
        rect.h = 40;
        check_texture_error(level->textures[1]); check_texture_error(level->textures[2]);
        if(level->charge_time == 1)
            SDL_RenderCopy(*ren, level->textures[2], NULL, &rect);
        else
            SDL_RenderCopy(*ren, level->textures[1], NULL, &rect);
    }

    // Score
    if(create_new == 1){
        SDL_DestroyTexture(*texture_score);
        SDL_Color color = {239,162,26};
        if (level->charge_time == 1){
            color.r = 119;
            color.g = 231;
            color.b = 247;
        }
        char* score_str = malloc(sizeof(char) * 100); score_str[0] = '\0';
        if(level->coop == 0)
            sprintf(score_str, "Score: %5d", level->score);
        else{
            sprintf(score_str, "P1: %5d    P2: %5d", level->score, level->coop_score);
        }

        SDL_Surface* surface_message = TTF_RenderText_Solid(level->fonts[1], score_str, color);
        *texture_score = SDL_CreateTextureFromSurface(*ren, surface_message);
        SDL_FreeSurface(surface_message);
        free(score_str);
    }
    rect.x = 25; rect.y = 28; rect.h = 26;
    if(level->coop == 0)
        rect.w = 80;
    else
        rect.w = 160;
    
    SDL_RenderCopy(*ren, *texture_score, NULL, &rect);

    // Win/Lost - Level
    if(create_new == 1){
        SDL_DestroyTexture(*texture_win);
        SDL_Surface* surface_message;
        char* level_str = malloc(sizeof(char) * 100); level_str[0] = '\0';

        if(level->game_win == 1){
            if (level->current_level == level->maps_len - 1){
                SDL_Color color = {50,200,50};
                surface_message = TTF_RenderText_Solid(level->fonts[1], "Game Win", color);
            }else{
                SDL_Color color = {255,128,0};
                surface_message = TTF_RenderText_Solid(level->fonts[1], "Level Win", color);
            }
            rect.y = 20;
            rect.h = 40;
        }else if(level->game_win == -1){
            SDL_Color color = {255,0,0};
            surface_message = TTF_RenderText_Solid(level->fonts[1], "Game Over", color);
            rect.y = 20;
            rect.h = 40;
        }else{
            SDL_Color color = {239,162,26};
            level_str = strcat(level_str, "Level: ");

            char str[10];
            sprintf(str, "%1i", level->current_level + 1);
            level_str = strcat(level_str, str);
            surface_message = TTF_RenderText_Solid(level->fonts[1], level_str, color);
            
            rect.y = 28;
            rect.h = 26;
        }
        *texture_win = SDL_CreateTextureFromSurface(*ren, surface_message);
        
        free(level_str);
        SDL_FreeSurface(surface_message);
    }
    rect.x = level->maps_size_x[level->current_level]/2 * 30;
    rect.w = 100;
    SDL_RenderCopy(*ren, *texture_win, NULL, &rect);    
}
void draw_background(SDL_Renderer** ren ,const int win_width, const int win_height){
    SDL_Rect rect;
    SDL_SetRenderDrawColor(*ren, 25, 25, 25, 255);               // 40 50 60
    rect.x = 0;
    rect.y = 0;
    rect.w = win_width;
    rect.h = win_height;
    SDL_RenderFillRect(*ren, &rect);

    SDL_SetRenderDrawColor(*ren, 39, 44, 48, 255);                 // 60 70 80     
    rect.x = 15;
    rect.y = 15;
    rect.w = win_width - 30;
    rect.h = 50;
    SDL_RenderFillRect(*ren, &rect);

    rect.x = 15;
    rect.y = 80;
    rect.w = win_width - 30;
    rect.h = win_height - 95;
    SDL_RenderFillRect(*ren, &rect);
}
void draw_entity(SDL_Renderer** ren, Entity* entity, Levels* level){
    int surface_type = 0, offset_x = 30, offset_y = 95;

    if(entity->type != 'p'){
        if(level->charge_time == 0){
            surface_type = (entity->direction * 2) + entity->style;
        }else{
            if( (int)(6000 - (SDL_GetTicks() - level->charge_start_time)) >= 0)
                surface_type = (4 * 2) + entity->style;
            else
                surface_type = (5 * 2) + entity->style;
        }
    }else{
        surface_type = ((entity->direction + 1) * 2) + entity->style;
    }
    check_texture_error(entity->textures[surface_type]);

    SDL_Rect rect;
    rect.x = offset_x + 30 * entity->pos_x + 3;
    rect.y = offset_y + 30 * entity->pos_y + 3;
    rect.w = 24;
    rect.h = 24;
    SDL_RenderCopy(*ren, entity->textures[surface_type], NULL, &rect);
    rect.w = 30;
    rect.h = 30;
}
void draw_level(SDL_Renderer** ren, Entity** entities, const int entities_len, Levels** level, const int win_width,const int scale){      
    SDL_Rect rect;
    double wall_x = 30, wall_y = 95;
    int no_points_left = 1;

    for (int y = 0; y < (*level)->maps_size_y[(*level)->current_level]; y++){
        for (int x = 0; x < (*level)->maps_size_x[(*level)->current_level]; x++){
            char letter = (*level)->maps[(*level)->current_level][to_1d(x, y, (*level)->maps_size_y[(*level)->current_level])];
            if (letter == '#' || letter == '-'){   

                rect.x = wall_x;
                rect.y = wall_y;
                rect.w = 30;  
                rect.h = 30;

                if (letter == '-'){                    
                    check_texture_error((*level)->textures[11]);
                    SDL_RenderCopy(*ren, (*level)->textures[11], NULL, &rect);
                }else{
                    char left = '/', right = '/', top = '/', down = '/';
                    if(x > 0)
                        left = (*level)->maps[(*level)->current_level][to_1d(x - 1, y, (*level)->maps_size_y[(*level)->current_level])];
                    if(x < (*level)->maps_size_x[(*level)->current_level] - 1)
                        right = (*level)->maps[(*level)->current_level][to_1d(x + 1, y, (*level)->maps_size_y[(*level)->current_level])];
                    if(y > 0)
                        top = (*level)->maps[(*level)->current_level][to_1d(x, y - 1, (*level)->maps_size_y[(*level)->current_level])];
                    if(y < (*level)->maps_size_y[(*level)->current_level] - 1)
                        down = (*level)->maps[(*level)->current_level][to_1d(x, y + 1, (*level)->maps_size_y[(*level)->current_level])];
                    
                    check_texture_error((*level)->textures[5]); check_texture_error((*level)->textures[6]); 
                    check_texture_error((*level)->textures[7]); check_texture_error((*level)->textures[8]); 
                    check_texture_error((*level)->textures[9]); check_texture_error((*level)->textures[10]); 
                    
                    
                    if(left == '#' && right == '#' && top == '#' && down == '#'){
                        SDL_RenderCopyEx(*ren, (*level)->textures[8], NULL, &rect, 0, 0, 0);
                    }else if(left != '#' && right != '#' && top != '#' && down != '#'){
                        SDL_RenderCopyEx(*ren, (*level)->textures[10], NULL, &rect, 0, 0, 0);
                    }else if(left == '#' && right == '#' && top == '#' && down != '#'){
                        SDL_RenderCopyEx(*ren, (*level)->textures[7], NULL, &rect, 0, 0, SDL_FLIP_VERTICAL);
                    }else if(left == '#' && right == '#' && top != '#' && down == '#'){
                        SDL_RenderCopyEx(*ren, (*level)->textures[7], NULL, &rect, 0, 0, 0);
                    }else if(left == '#' && right != '#' && top == '#' && down == '#'){
                        SDL_RenderCopyEx(*ren, (*level)->textures[7], NULL, &rect, 90, 0, 0);
                    }else if(left != '#' && right == '#' && top == '#' && down == '#'){
                        SDL_RenderCopyEx(*ren, (*level)->textures[7], NULL, &rect, 270, 0, 0);
                    }else if(right == '#' && down == '#'){
                        SDL_RenderCopy(*ren, (*level)->textures[6], NULL, &rect);
                    }else if(left == '#' && down == '#'){
                        SDL_RenderCopyEx(*ren, (*level)->textures[6], NULL, &rect, 0, 0, SDL_FLIP_HORIZONTAL);
                    }else if(left == '#' && top == '#'){
                        SDL_RenderCopyEx(*ren, (*level)->textures[6], NULL, &rect, 0, 0, SDL_FLIP_VERTICAL | SDL_FLIP_HORIZONTAL);
                    }else if(right == '#' && top == '#'){
                        SDL_RenderCopyEx(*ren, (*level)->textures[6], NULL, &rect, 0, 0, SDL_FLIP_VERTICAL);
                    }else if(top == '#' || down == '#'){
                        if(top != '#')
                            SDL_RenderCopyEx(*ren, (*level)->textures[9], NULL, &rect, 0, 0, 0);
                        else if(down != '#')
                            SDL_RenderCopyEx(*ren, (*level)->textures[9], NULL, &rect, 180, 0, 0);
                        else
                            SDL_RenderCopy(*ren, (*level)->textures[5], NULL, &rect);
                    }else if(left == '#' || right == '#'){
                        if(left != '#')
                            SDL_RenderCopyEx(*ren, (*level)->textures[9], NULL, &rect, 270, 0, 0);
                        else if(right != '#')
                            SDL_RenderCopyEx(*ren, (*level)->textures[9], NULL, &rect, 90, 0, 0);
                        else
                            SDL_RenderCopyEx(*ren, (*level)->textures[5], NULL, &rect, 90, 0, 0);
                    }
                    //SDL_RenderCopy(*ren, (*level)->textures[4], NULL, &rect);
                }                
                                   
            }else if (letter == '.'){
                no_points_left = 0;

                SDL_SetRenderDrawColor(*ren, 119, 231, 247, 255);        // 150 150 50 
                rect.x = wall_x + 12;
                rect.y = wall_y + 12;
                rect.w = 6;
                rect.h = 6;
                SDL_RenderFillRect(*ren, &rect); 
                rect.w = 30;
                rect.h = 30;
            }else if (letter != ' '){
                if(letter != 'o' && letter != 't'){
                    fprintf(stderr, "Parametr in level is invalid: \tchar %c (%i) on x%i y%i\n", letter, (int)letter, x, y);
                    exit(1); 
                }                 
                check_texture_error((*level)->textures[0]);
                check_texture_error((*level)->textures[2]); check_texture_error((*level)->textures[3]);

                if(letter == 'o'){
                    rect.x = wall_x + 3;
                    rect.y = wall_y + 3;
                    rect.w = 24;
                    rect.h = 24;
                
                    SDL_RenderCopy(*ren, (*level)->textures[0], NULL, &rect);
                }else{
                    rect.x = wall_x;
                    rect.y = wall_y;
                    rect.w = 30;
                    rect.h = 30;

                    if(x < (*level)->maps_size_x[(*level)->current_level]/ 2)
                        SDL_RenderCopy(*ren, (*level)->textures[2], NULL, &rect);
                    else
                        SDL_RenderCopyEx(*ren, (*level)->textures[2], NULL, &rect, 0, 0, SDL_FLIP_HORIZONTAL);
                    
                }

                rect.w = 30;
                rect.h = 30;
            }

            if(wall_x/scale + rect.w >= win_width - 30)
                wall_x = 30 / scale;
            else
                wall_x += rect.w;
            
        }   
        wall_y += 30;     
    }
    
    for (int i = 0; i < entities_len; i++){
        if((*level)->coop == 1 || i != (*level)->coop_pl_index)
            draw_entity(ren, entities[i], (*level));    
    }

    if(no_points_left == 1)
        (*level)->game_win = 1;
}

void draw_debug(SDL_Renderer** ren, Entity* entity, const int red, const int green, const int blue){
    SDL_Rect rect;
    SDL_SetRenderDrawColor(*ren, red, green, blue, 10);
    rect.x = 35 + 30 * round(entity->pos_x);
    rect.y = 100 + 30 * round(entity->pos_y);
    rect.w = 20;
    rect.h = 20;
    SDL_RenderFillRect(*ren, &rect);
}
