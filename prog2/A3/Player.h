#ifndef __PLAYER__
#define __PLAYER__

#include "init.h"

typedef struct{
    int pos_x;
    int pos_y;
    int vx;
    int vy;
    int hp;
} Player;

Player createPlayer();

void updatePlayer(Player *player, Input input, int hp);

#endif