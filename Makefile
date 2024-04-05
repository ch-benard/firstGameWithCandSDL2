clean:
	rm -f bin/*
build:
	gcc -o bin/firstGameInCwithSDL2 src/main.c `sdl2-config --cflags --libs`
exec:
	./bin/firstGameInCwithSDL2