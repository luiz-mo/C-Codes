#ifndef __init__
#define __init__

#define GRAVITY 1

#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

typedef enum{
    HOME,
    RUNNING,
    PAUSED,
    EXIT
} state;

typedef struct{
    int left;
    int right;
    int jump;
    int crouch;
} Input;

typedef struct{
    float pos_x;
    float pos_y;
    float width;
    float height;
} Platform;

typedef struct{
    Platform *plats;
    int n_plats;
} Map;

void init();

Input createInput();

Platform createPlatforms();

#endif