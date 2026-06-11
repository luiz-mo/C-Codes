#include "Map.h"

Enemy createEnemy(ALLEGRO_BITMAP *sprite){
    Enemy enemy;

    enemy.pos_x = 700;
    enemy.pos_y = 480;
    enemy.width = 40;
    enemy.height = 50;
    enemy.vx = 0;
    enemy.vy = 0;
    enemy.dmg = 10;
    enemy.curr_frame = 0;
    enemy.frame_timer = 0;
    enemy.state = E_IDLE;

    enemy.sprite = sprite;
    
    return enemy;
}

int createMap(Map *map, ALLEGRO_BITMAP *sprite){
    if(!(map->enemies = malloc(sizeof(Enemy) * 10)))
        return 1;

    Platform ground = {0, 530, 5000, 70};
    Platform plat1 = {300, 430, 200, 30};
    Platform plat2 = {700, 320, 150, 30};

    map->plats[0] = ground;
    map->plats[1] = plat1;
    map->plats[2] = plat2;

    map->n_plats = 3;
    
    map->enemies[0] = createEnemy(sprite);
    map->n_enemies = 1;

    return 0;
}

void drawEnemy(Map map, Camera cam){
    Enemy e = map.enemies[0];

    int sprite_x;
    int sprite_y;
    int sprite_w = 56;
    int sprite_h = 40;

    switch(e.state){
        case E_IDLE:
            sprite_x = e.curr_frame * sprite_w;
            sprite_y = 0;
            break;

        case E_WALK:
            sprite_x = e.curr_frame * sprite_w;
            sprite_y = 40;
            break;

        case E_JUMP:
            sprite_x = e.curr_frame * sprite_w;
            sprite_y = 80;
            break;
    }

    al_draw_bitmap_region(
        e.sprite,
        sprite_x,
        sprite_y,
        sprite_w,
        sprite_h,
        e.pos_x - cam.x,
        e.pos_y - cam.y,
        0
    );
}