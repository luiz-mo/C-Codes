#ifndef __init__
#define __init__

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

void init();

Input createInput();

#endif