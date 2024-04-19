clean:
	rm -f bin/*
build:
	gcc -Wall -o bin/game src/main.c src/game.c src/TN2D/TN2D.c src/TN2D/TN2D_Graphics.c src/TN2D/TN2D_Ttf.c src/TN2D/TN2D_Keyboard.c `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf -lSDL2 -lm
build_game2:
	gcc -Wall -std=c99 -o bin/game2 src/main2.c -lSDL2 -lSDL2_image -lm
exec:
	./bin/firstGameInCwithSDL2
	