clean:
	rm -f bin/*
build:
	gcc -o bin/game src/main.c src/tn2d/tn2d_graphics.c `sdl2-config --cflags --libs` -lSDL2_image -lSDL2_ttf
exec:
	./bin/firstGameInCwithSDL2
	