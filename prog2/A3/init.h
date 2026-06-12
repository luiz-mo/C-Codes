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
    EXIT,
    CONFIRM,
    GAME_OVER,
    GAME_WON
} state;

typedef struct{
    int left;
    int right;
    int jump;
    int crouch;
} Input;

typedef struct{
    float x;
    float y;
} Camera;

void initAddons();

Input createInput();

Camera createCamera();

#endif