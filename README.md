![Size](https://img.shields.io/github/repo-size/sobotat/Pacman?style=for-the-badge)
![Version](https://img.shields.io/github/v/release/sobotat/Pacman?style=for-the-badge)

# PACMAN Game
Made by: Tomáš Sobota

### Warning:
    - game was developed only for Linux with SDL library.


The Pacman game originated as a college programming project.

There are 4 levels in the game, dangerous ghosts and, most importantly, the chance to experience the old days as in the creation of the original Pacman.

**Have a nice play**

---

## Screenshots
![Game](/art/pacman_art_v1.2_1.png)

![GameCoop](/art/pacman_art_v1.2_2.png)

---

## How to install and run
### How to run on Linux
1. Use install script
    ```bash
    $ ./install.sh
    ```
2. Run it
    ```bash
    $ cd build
    $ ./pacman
    ```

### How to run on Windows 11
<details>
<summary>Show</summary>

1. Install **wsl** in Powershell
    ```bash
    C:\> wsl --install
    ```

2. Install **Ubuntu**
   ```bash
   C:\> wsl --install -d Ubuntu
   ```

3. Run **wsl**, after that you will have full Ubuntu terminal
   ```bash
   C:\> wsl
   ```
</details>

---

## Changelog:
<details>    
<summary>Show</summary>

    - v1.0
        - dropping the full version of the game
    - v1.1 
        - coop was added
        - new Pacman textures to distinguish 2 players
    - v1.1.1 
        - coop score was added
        - score of killing ghosts divided into players
        - added coop score to hud
    - v1.2
        - design overhaul
        - added new maps
    - v1.2.1
        - added install script
    - v1.2.2
        - added Start, Win, Dead screen
        - added Window Scale (using with - and =)
        - improved player movement
        - fixed player stucking after dead
        - fixed locating player in level
    - v1.2.3
        - improved player movement

</details>

---

## Controls:
|Key     |Info                                         |
|:------:|:--------------------------------------------|
|arrows  |*movement of player, start game*             |
|w,s,a,d |*movement of co_player*                      |
|space   |*start the game*                             |
|esc     |*pause the game*                             |
|r       |*restart the game*                           |
|l       |*Level changing (only for level checking :D)*|
|-,=     |*Window size chaning*                        |

---

## Arguments:
|Num|Argument     |Info                 |Default |On  |
|:---:|:---------:|:--------------------|-------:|---:|
|**1**|coop_mode  |*enable coop mode*   |0       |1   |
|**2**|move_speed |*change move speed*  |0, 4    |1-15|
|**3**|maps_size  |*number of levels*   |0, 4    |1-99|
|**4**|debug      |*enable debug mode*  |0       |1   |

---

## Map editing:
    a player 'p' is needed in the map to run the game properly !!!
    maps can be modified in folder "res/levels"
    
    level name must continue after last name
    current maximum number is 99 (100 levels)

    size of x and y must be in the first row of the file

### Legend: 
|char   |info                 |
|:-----:|:--------------------|
|p      |*player*             |
|c,m,y,r|*ghosts*             |
|#      |*walls*              |
|-      |*doors for ghosts*   |
|o      |*charges*            |
|.      |*points*             |
