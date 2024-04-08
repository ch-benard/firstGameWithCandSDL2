clean:
	rm -f bin/*
build:
	gcc -Wall -o bin/game src/main.c src/tn2d/tn2d.c src/tn2d/tn2d_graphics.c src/tn2d/tn2d_ttf.c src/tn2d/tn2d_keyboard.c `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf
exec:
	./bin/firstGameInCwithSDL2
	