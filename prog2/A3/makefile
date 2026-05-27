CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -std=c99
ALLEGRO = $(shell pkg-config --libs --cflags\
			allegro-5 allegro_main-5 \
			allegro_font-5 allegro_primitives-5\
			allegro_ttf-5 allegro_image-5)

HDR = 

OBJ = 

all: game.o
	$(CC) game.o -o game $(ALLEGRO)

game.o: game.c
	$(CC) $(CFLAGS) $(ALLEGRO) -c game.c

clean:
	rm *.o game