#ifndef __MAP__
#define __MAP__

#include <stdlib.h>
#include "init.h"

typedef struct{
    float pos_x;
    float pos_y;
    float width;
    float height;

    int moving;
    int vx;
    int lim_left;
    int lim_right;
} Platform;

typedef enum{
    E_IDLE,
    E_WALK,
    E_JUMP
} Enemy_State;

typedef struct{
    float pos_x;
    float pos_y;
    float start_y;
    float width;
    float height;

    float vx;
    float vy;

    float dmg;

    float lim_left;
    float lim_right;
    int direction;
    int wait_timer;

    ALLEGRO_BITMAP *sprite;
    int curr_frame;
    int frame_timer;
    Enemy_State state;
} Enemy;

typedef struct{
    float pos_x;
    float pos_y;
    float width;
    float height;

    int dmg;
} Spike;

typedef struct{
    float pos_x;
    float pos_y;

    float width;
    float height;

    int dmg;
} Gas;

typedef struct{
    float pos_x;
    float pos_y;

    float width;
    float height;
} Omnitrix;

typedef struct{
    Platform plats[20];
    int n_plats;

    Enemy *enemies;
    int n_enemies;

    Platform pits[10];
    int n_pits;

    Spike spikes[10];
    int n_spikes;

    Gas gases[10];
    int n_gases;

    Omnitrix omnitrix;
} Map;

int createMap(Map *map, ALLEGRO_BITMAP *sprite);

Enemy createEnemy(ALLEGRO_BITMAP *s, float x, float y, float lim_l, float lim_r, Enemy_State type);

void updateEnemy(Map *map);

void updatePlatforms(Map *map);

void drawEnemy(Enemy e, Camera cam);

void drawPlatform(Platform plat, ALLEGRO_BITMAP *sprite, Camera cam);

void drawSpike(Spike s, ALLEGRO_BITMAP *sprite, Camera cam);

void drawPit(Platform pit, ALLEGRO_BITMAP *sprite, Camera cam);

void drawGas(Gas gas, Camera cam);

void drawOmnitrix(ALLEGRO_BITMAP *sprite, Map map, Camera cam);

#endif