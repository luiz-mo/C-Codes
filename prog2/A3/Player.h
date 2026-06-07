#ifndef __PLAYER__
#define __PLAYER__

#include "init.h"

typedef struct{
    int pos_x;
    int pos_y;
    int vx;
    int vy;
    int height;
    int width;
    int hp;
    int on_ground;
} Player;

Player createPlayer();

void updatePlayer(Player *player, Input input, Map map, int hp);

#endif