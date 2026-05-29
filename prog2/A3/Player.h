#ifndef __PLAYER__
#define __PLAYER__

#include "init.h"

typedef struct{
    int pos_x;
    int pos_y;
    int hp;
} Player;

Player createPlayer();

#endif