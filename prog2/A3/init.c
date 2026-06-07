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

Map createMap(){
    Map map;

    Platform ground = {0, 600, 1280, 70};
    Platform plat1 = {300, 450, 200, 30};
    Platform plat2 = {700, 350, 150, 30};

    map.plats[0] = ground;
    map.plats[1] = plat1;
    map.plats[2] = plat2;

    map.n_plats = 3;
    
    return map;
}