#ifndef __PLAYER__
#define __PLAYER__

#include "init.h"

typedef enum{
    IDLE,
    RUN,
    CROUCH,
    JUMP,
    FALL
} player_state;

typedef struct{
    ALLEGRO_BITMAP *sprites;
    float pos_x;
    float pos_y;
    int vx;
    int vy;
    int height;
    int width;
    int hp;
    int on_ground;
    player_state state;
    int curr_frame;
    int frame_timer;
} Player;

Player createPlayer();

void drawPlayer(Player player, Camera cam);

void updatePlayer(Player *player, Input input, Map map);

#endif