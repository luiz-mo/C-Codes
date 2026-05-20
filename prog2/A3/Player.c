#ifndef __PLAYER__
#define __PLAYER__

#include <allegro5/allegro5.h>

typedef struct{
    int pos_x;
    int pos_y;
    int hp;
    ALLEGRO_BITMAP sprite;
} Player;

#endif