CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -std=c99
ALLEGRO = $(shell pkg-config --libs --cflags \
        	allegro-5 allegro_main-5 \
            allegro_font-5 allegro_primitives-5 \
            allegro_ttf-5 allegro_image-5)

HDR = Screens.h
OBJ = game.o Screens.o

all: game

game: $(OBJ)
	$(CC) $(OBJ) -o game $(ALLEGRO)

game.o: game.c $(HDR)
	$(CC) $(CFLAGS) $(ALLEGRO) -c game.c

Screens.o: Screens.c $(HDR)
	$(CC) $(CFLAGS) $(ALLEGRO) -c Screens.c

clean:
	rm -f *.o game