#include "init.h"

void initAddons(){
    al_init();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_install_keyboard();
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

    Platform ground = {0, 530, 10000, 70};
    Platform plat1 = {300, 430, 200, 30};
    Platform plat2 = {700, 320, 150, 30};

    map.plats[0] = ground;
    map.plats[1] = plat1;
    map.plats[2] = plat2;

    map.n_plats = 3;
    
    return map;
}

Camera createCamera(){
    Camera cam;

    cam.x = 0;
    cam.y = 0;

    return cam;
}