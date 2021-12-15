______                                
| ___ \                               
| |_/ /_ _  ___ _ __ ___   __ _ _ __  
|  __/ _` |/ __| '_ ` _ \ / _` | '_ \ 
| | | (_| | (__| | | | | | (_| | | | |
\_|  \__,_|\___|_| |_| |_|\__,_|_| |_|

Made by: Tomáš Sobota

Warning:
    - game was developed only for Linux with SDL library.

How to start:
    A. use 'make' command in the folder for start a game.
    B. if you want play with friends use command ./pacman 1
    C. for default run of game write ./pacman

The Pacman game originated as a college programming project.
There are 3 levels in the game, dangerous ghosts and, most importantly, 
the chance to experience the old days as in the creation of the original Pacman.

Have a nice play

--------------------------------------------------------------------------------

Changelog:
    v1.0 - dropping the full version of the game
    v1.1 - coop was added, new Pacman textures to distinguish 2 players

--------------------------------------------------------------------------------

Controls:
    wsad - movement of player, start game
    space - start game
    esc - pause
    r - restart the game
    l - Level changing (only for level checking :D)

--------------------------------------------------------------------------------

Map editing:
    a player 'p' is needed in the map to run the game properly !!!¨
    maps can be modified in folder "res/levels"
    
    level name must continue after last name
    current maximum number is 99 (100 levels)

    size of x and y must be in the first row of the file

    Legend:
        p - player
        c,m,y,r - ghosts
        # - Wall
        - - up for ghosts
        o - charge
        . - point
                                                                                
--------------------------------------------------------------------------------

Arguments:
    1. coop_mode - to enable coop mode write 1 (default is 0)
    2. move_speed - chance move speed (default is 4), 
                    maximum recomended speed is 15, 0 to use default number 
    3. maps_size - number of levels to load (default is 3), 0 to use default number
    4. debug - choose 0 or 1 to enable debug mode (default is 0)