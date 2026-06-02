#include "init.h"

void init(){
    al_init();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_install_keyboard();
    al_install_mouse();   
}

Input createInput(){
    Input input;

    input.left = 0;
    input.right = 0;
    input.jump = 0;
    input.crouch = 0;

    return input;
}

Platform createPlatforms(){
    Platform plat;

    plat.pos_x = 0;
    plat.pos_y = 650;
    plat.width = 1280;
    plat.height = 70;

    return plat;
}