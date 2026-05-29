CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -std=c99
ALLEGRO = $(shell pkg-config --libs --cflags \
        	allegro-5 allegro_main-5 \
            allegro_font-5 allegro_primitives-5 \
            allegro_ttf-5 allegro_image-5)

HDR = Player.h Screens.h init.h
OBJ = game.o Player.o Screens.o init.o

all: game

game: $(OBJ)
	$(CC) $(OBJ) -o game $(ALLEGRO)

game.o: game.c $(HDR)
	$(CC) $(CFLAGS) $(ALLEGRO) -c game.c

Player.o: Player.c $(HDR)
	$(CC) $(CFLAGS) $(ALLEGRO) -c Player.c

Screens.o: Screens.c $(HDR)
	$(CC) $(CFLAGS) $(ALLEGRO) -c Screens.c

init.o: init.c $(HDR)
	$(CC) $(CFLAGS) $(ALLEGRO) -c init.c

clean:
	rm -f *.o game