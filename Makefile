all:
	# gcc main.c src/*.c -o pacman -I/usr/include/SDL2 -lSDL2 -lSDL2_image -lSDL2_ttf -fsanitize=address -lm
	gcc main.c src/*.c -o pacman -I/usr/include/SDL2 -lSDL2 -lSDL2_image -lSDL2_ttf -lm
	#./pacman