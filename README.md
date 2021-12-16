![Size](https://img.shields.io/github/repo-size/sobotat/Pacman?style=for-the-badge)
![Version](https://img.shields.io/github/v/release/sobotat/Pacman?style=for-the-badge)
![Downloads](https://img.shields.io/github/downloads/sobotat/Pacman/total?color=%23&style=for-the-badge)

# PACMAN Game
Made by: Tomáš Sobota

### Warning:
    - game was developed only for Linux with SDL library.


The Pacman game originated as a college programming project.

There are 3 levels in the game, dangerous ghosts and, most importantly, the chance to experience the old days as in the creation of the original Pacman.

**Have a nice play**

---

### Screenshots
![Game](/res/pacman_art.png)

![GameCoop](/res/pacman_art_coop.png)

---

### How to install and run
1. Install SDL libs:

    - Debian, Ubuntu.. :
        ```bash
        $ sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev cmake pkg-config
        ```
2. Build it
    ```bash
    $ make
    ```

3. Run it
    ```bash
    $ ./pacman
    ```

---

### Changelog:
    - v1.0
        - dropping the full version of the game
    - v1.1 
        - coop was added
        - new Pacman textures to distinguish 2 players
    - v1.1.1 
        - coop score was added
        - score of killing ghosts divided into players
        - added coop score to hud

---

### Controls:
|key  |info                                         |
|:---:|:--------------------------------------------|
|wsad |*movement of player, start game*             |
|space|*start the game*                             |
|esc  |*pause the game*                             |
|r    |*restart the game*                           |
|l    |*Level changing (only for level checking :D)*|

---

### Arguments:

1. **coop_mode** - to enable coop mode write 1 (default is 0)
2. **move_speed** - change move speed (default is 4), 
                    maximum recomended speed is 15, 0 to use default number 
3. **maps_size** - number of levels to load (default is 3), 0 to use default number
4. **debug** - choose 0 or 1 to enable debug mode (default is 0)

---

### Map editing:
    a player 'p' is needed in the map to run the game properly !!!
    maps can be modified in folder "res/levels"
    
    level name must continue after last name
    current maximum number is 99 (100 levels)

    size of x and y must be in the first row of the file

### Legend: 
|char |info                   |
|:-----:|:--------------------|
|p      |*player*             |
|c,m,y,r|*ghosts*             |
|#      |*walls*              |
|-      |*doors for ghosts*   |
|o      |*charges*            |
|.      |*points*             |
