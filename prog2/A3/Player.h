#ifndef __PLAYER__
#define __PLAYER__

#include "init.h"

typedef enum{
    IDLE,
    RUNNING,
    CROUCHED,
    JUMPING
} player_state;

typedef struct{
    float pos_x;
    float pos_y;
    int vx;
    int vy;
    int height;
    int width;
    int hp;
    int on_ground;
    player_state state;
} Player;

Player createPlayer();

void updatePlayer(Player *player, Input input, Map map);

#endif