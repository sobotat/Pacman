#include "lib/draw.h"

void draw_start_screen(SDL_Renderer** ren, Levels* level, const int win_width, const int win_height, const int time, const int create_new){
    SDL_Rect rect;

    // Background
    rect.x = 0; rect.y = 0;
    rect.w = win_width; rect.h = win_height;
    SDL_SetRenderDrawColor(*ren, 25, 25, 25, 255); 
    SDL_RenderFillRect(*ren, &rect);

    //rect.x = win_width/2 - 240; rect.y = 40;
    //rect.w = 480; rect.h = win_height - 80;
    rect.x = win_width/2 - 240; rect.y = win_height/2 - 100;
    rect.w = 480; rect.h = 200;
    SDL_SetRenderDrawColor(*ren, 39, 44, 48, 255); 
    SDL_RenderFillRect(*ren, &rect);
    SDL_SetRenderDrawColor(*ren, 239, 162, 26, 255);
    SDL_RenderDrawRect(*ren, &rect);

    // Game Name
    if(create_new == 1){
        SDL_Color color = {255,128,0};
        SDL_Surface* surface_message = TTF_RenderText_Solid(level->fonts[1], "Pacman", color);;
        
        SDL_Texture* texture_name = SDL_CreateTextureFromSurface(*ren, surface_message);
        SDL_FreeSurface(surface_message);
        
        //rect.x = win_width/2 - 200; rect.y = 60;
        rect.x = win_width/2 - 200; rect.y = win_height/2 - 70;
        rect.w = 400; rect.h = 60;
        SDL_RenderCopy(*ren, texture_name, NULL, &rect);    
        SDL_DestroyTexture(texture_name);
    }

    // Help how to start game - Press Space
    if(time % 2 == 0){
        SDL_Color color = {200,200,200};
        SDL_Surface* surface_message = TTF_RenderText_Solid(level->fonts[1], "Press < Space >", color);;
        
        SDL_Texture* texture_name = SDL_CreateTextureFromSurface(*ren, surface_message);
        SDL_FreeSurface(surface_message);
        
        // rect.x = win_width/2 - 80; rect.y = win_height - 80;
        rect.x = win_width/2 - 80; rect.y = win_height/2 + 25;
        rect.w = 190; rect.h = 25;
        SDL_RenderCopy(*ren, texture_name, NULL, &rect);    
        SDL_DestroyTexture(texture_name);
    }

    check_texture_error(level->entities[0][level->pl_index[level->current_level]]->textures[5]);
    rect.x = win_width/2 - (4 - time * 40) - (2 * 40) - 20;
    rect.y = win_height/2 + 130 - 15;
    rect.w = 60;
    rect.h = 60;
    SDL_RenderCopy(*ren, level->entities[0][level->pl_index[level->current_level]]->textures[5], NULL, &rect); 
    for (int i = 4 - time; i > 0; i--){
        check_texture_error(level->textures[0]);
        rect.x = win_width/2 - (i * 40) + (2 * 40) + 40;
        rect.y = win_height/2 + 130;
        rect.w = 30;
        rect.h = 30;
        SDL_RenderCopy(*ren, level->textures[0], NULL, &rect);    
    }
}
void draw_finish_screen(SDL_Renderer** ren, SDL_Texture** texture_score, SDL_Texture** texture_win, SDL_Texture** texture_continue, Levels* level, const int win_width, const int win_height, const int time, const int create_new){
    SDL_Rect rect;

    // Background
    rect.x = 0; rect.y = 0;
    rect.w = win_width; rect.h = win_height;
    SDL_SetRenderDrawColor(*ren, 25, 25, 25, 255); 
    SDL_RenderFillRect(*ren, &rect);

    rect.x = win_width/2 - 240; rect.y = win_height/2 - 90;
    rect.w = 480; rect.h = 180;
    SDL_SetRenderDrawColor(*ren, 39, 44, 48, 255); 
    SDL_RenderFillRect(*ren, &rect);
    SDL_SetRenderDrawColor(*ren, 239, 162, 26, 255);
    SDL_RenderDrawRect(*ren, &rect);
    
    // Score
    if(create_new == 1){
        SDL_DestroyTexture(*texture_score);
        SDL_Color color = {239,162,26};
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
    rect.x = win_width/2 - 100; rect.y = win_height/2 + 30; rect.w = 200; rect.h = 40;
    SDL_RenderCopy(*ren, *texture_score, NULL, &rect);


    // Win/Lost
    if(create_new == 1){
        SDL_DestroyTexture(*texture_win);
        SDL_Surface* surface_message;

        if(level->game_win == 1){
            if (level->current_level == level->maps_len - 1){
                SDL_Color color = {50,200,50};
                surface_message = TTF_RenderText_Solid(level->fonts[1], "Game Win", color);
            }else{
                SDL_Color color = {255,128,0};
                surface_message = TTF_RenderText_Solid(level->fonts[1], "Level Win", color);
            }
        }else if(level->game_win == -1){
            SDL_Color color = {255,0,0};
            surface_message = TTF_RenderText_Solid(level->fonts[1], "Game Over", color);            
        }

        if(level->game_win != 0){
            *texture_win = SDL_CreateTextureFromSurface(*ren, surface_message);
            SDL_FreeSurface(surface_message);
        }
    }
    if(level->game_win != 0){
        rect.x = win_width/2 - 200;
        rect.y = win_height/2 - 70;            
        rect.w = 400;
        rect.h = 80;
        SDL_RenderCopy(*ren, *texture_win, NULL, &rect);    
    }

    // Continue time / Press R to Restart
    if(level->game_win != 0){
        if(create_new == 1){
            SDL_DestroyTexture(*texture_continue);
            SDL_Surface* surface_message;
            char* time_str = malloc(sizeof(char) * 100); time_str[0] = '\0';

            SDL_Color color = {239,162,26};
            if(level->game_win == 1 && (level->maps_len -1 != level->current_level))
                sprintf(time_str, "Continue in %2i", time);
            else
                sprintf(time_str, "Press R to restart");
            surface_message = TTF_RenderText_Solid(level->fonts[1], time_str, color);
            
            rect.y = win_height - 36; rect.h = 24;
            *texture_continue = SDL_CreateTextureFromSurface(*ren, surface_message);
            
            free(time_str);
            SDL_FreeSurface(surface_message);
        }   
        rect.x = win_width/2 - 80;
        rect.w = 160;
        SDL_RenderCopy(*ren, *texture_continue, NULL, &rect);    
    }
}

void draw_hud(SDL_Renderer** ren, SDL_Texture** texture_score, SDL_Texture** texture_win, Levels* level, const int win_width, const int create_new){
    SDL_Rect rect;

    // HP 
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

    // Level
    if(create_new == 1){
        SDL_DestroyTexture(*texture_win);
        SDL_Surface* surface_message;
        char* level_str = malloc(sizeof(char) * 100); level_str[0] = '\0';

        if(level->game_win == 0){
            SDL_Color color = {239,162,26};
            level_str = strcat(level_str, "Level: ");

            char str[10];
            sprintf(str, "%1i", level->current_level + 1);
            level_str = strcat(level_str, str);
            surface_message = TTF_RenderText_Solid(level->fonts[1], level_str, color);
            
            rect.y = 28;
            rect.h = 26;
            *texture_win = SDL_CreateTextureFromSurface(*ren, surface_message);
        }       
        
        free(level_str);
        SDL_FreeSurface(surface_message);
    }
    rect.x = win_width/2 - 50;
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
void draw_entity(SDL_Renderer** ren, Entity* entity, Levels* level, const double win_scale){
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
    rect.x = offset_x + (3 * win_scale) + entity->pos_x * 30 * win_scale;
    rect.y = offset_y + (3 * win_scale) + entity->pos_y * 30 * win_scale;
    rect.w = 24 * win_scale;
    rect.h = 24 * win_scale;
    SDL_RenderCopy(*ren, entity->textures[surface_type], NULL, &rect);
}
void draw_level(SDL_Renderer** ren, Entity** entities, const int entities_len, Levels** level, const int win_width, const double win_scale,const int scale){      
    SDL_Rect rect;
    //double wall_x = 30 - (30 * win_scale /4), wall_y = 95 - (60 * win_scale /3);
    double wall_x = 30, wall_y = 95;
    int offset_x = 30, offset_y = 95;
    int no_points_left = 1;

    for (int y = 0; y < (*level)->maps_size_y[(*level)->current_level]; y++){
        for (int x = 0; x < (*level)->maps_size_x[(*level)->current_level]; x++){
            char letter = (*level)->maps[(*level)->current_level][to_1d(x, y, (*level)->maps_size_y[(*level)->current_level])];
            if (letter == '#' || letter == '-'){   

                // rect.x = wall_x * win_scale;
                // rect.y = wall_y * win_scale;
                rect.x = offset_x + x * 30 * win_scale;
                rect.y = offset_y + y * 30 * win_scale;
                rect.w = 30 * win_scale;  
                rect.h = 30 * win_scale;

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
                rect.x = offset_x + (12 * win_scale) + x * 30 * win_scale;
                rect.y = offset_y + (12 * win_scale) + y * 30 * win_scale;
                rect.w = 6 * win_scale;
                rect.h = 6 * win_scale;
                SDL_RenderFillRect(*ren, &rect); 
            }else if (letter != ' '){
                if(letter != 'o' && letter != 't'){
                    fprintf(stderr, "Parametr in level is invalid: \tchar %c (%i) on x%i y%i\n", letter, (int)letter, x, y);
                    exit(1); 
                }                 
                check_texture_error((*level)->textures[0]);
                check_texture_error((*level)->textures[2]); check_texture_error((*level)->textures[3]);

                if(letter == 'o'){
                    rect.x = offset_x + (3 * win_scale) + x * 30 * win_scale;
                    rect.y = offset_y + (3 * win_scale) + y * 30 * win_scale;
                    rect.w = 24 * win_scale;
                    rect.h = 24 * win_scale;
                
                    SDL_RenderCopy(*ren, (*level)->textures[0], NULL, &rect);
                }else{
                    rect.x = offset_x + x * 30 * win_scale;
                    rect.y = offset_y + y * 30 * win_scale;
                    rect.w = 30 * win_scale;
                    rect.h = 30 * win_scale;

                    if(x < (*level)->maps_size_x[(*level)->current_level]/ 2)
                        SDL_RenderCopy(*ren, (*level)->textures[2], NULL, &rect);
                    else
                        SDL_RenderCopyEx(*ren, (*level)->textures[2], NULL, &rect, 0, 0, SDL_FLIP_HORIZONTAL);
                }
            }
        } 

    }
    
    for (int i = 0; i < entities_len; i++){
        if((*level)->coop == 1 || i != (*level)->coop_pl_index[(*level)->current_level])
            draw_entity(ren, entities[i], (*level), win_scale);    
    }

    if(no_points_left == 1)
        (*level)->game_win = 1;
}

void draw_debug(SDL_Renderer** ren, Entity* entity, const int red, const int green, const int blue, const double win_scale){
    SDL_Rect rect;
    SDL_SetRenderDrawColor(*ren, red, green, blue, 255);
    rect.x = 35 + round(entity->pos_x) * 30 * win_scale;
    rect.y = 100 + round(entity->pos_y) * 30 * win_scale;
    rect.w = 20 * win_scale;
    rect.h = 20 * win_scale;
    SDL_RenderFillRect(*ren, &rect);
}
