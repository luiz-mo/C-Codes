#ifndef __MAP__
#define __MAP__

#include <stdlib.h>
#include "init.h"

typedef struct{
    float pos_x;
    float pos_y;
    float width;
    float height;
} Platform;

typedef enum{
    E_IDLE,
    E_WALK,
    E_JUMP
} Enemy_State;

typedef struct{
    float pos_x;
    float pos_y;
    float width;
    float height;
    float vx;
    float vy;
    float dmg;
    ALLEGRO_BITMAP *sprite;
    int curr_frame;
    int frame_timer;
    Enemy_State state;
} Enemy;

typedef struct{
    Platform plats[10];
    int n_plats;
    Enemy *enemies;
    int n_enemies;
    Platform holes[10];
    int n_holes;
} Map;

int createMap(Map *map, ALLEGRO_BITMAP *sprite);

void drawEnemy(Map map, Camera cam);

#endif