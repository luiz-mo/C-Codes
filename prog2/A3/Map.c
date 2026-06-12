#include "Map.h"

Enemy createEnemy(ALLEGRO_BITMAP *s, float x, float y, float lim_l, float lim_r, Enemy_State type){
    Enemy enemy;

    enemy.pos_x = x;
    enemy.pos_y = y;
    enemy.start_y = y;
    enemy.width = 40;
    enemy.height = 50;
    enemy.vx = 0;
    enemy.vy = 0;
    enemy.dmg = 10;
    enemy.lim_left = lim_l;
    enemy.lim_right = lim_r;
    enemy.direction = 1;
    enemy.wait_timer = 0;
    enemy.curr_frame = 0;
    enemy.frame_timer = 0;
    enemy.state = type;

    enemy.sprite = s;
    
    return enemy;
}

Spike createSpike(float x, float y, float w, float h){
    Spike spike;

    spike.pos_x = x;
    spike.pos_y = y;
    spike.width = w;
    spike.height = h;
    spike.dmg = 20;

    return spike;
}

Gas createGas(float x, float y, float w, float h){
    Gas gas;

    gas.pos_x = x;
    gas.pos_y = y;
    gas.width = w;
    gas.height = h;

    gas.dmg = 2;

    return gas;
}

int createMap(Map *map, ALLEGRO_BITMAP *sprite){
    
    if(!(map->enemies = malloc(sizeof(Enemy) * 10)))
        return 1;

    Platform ground1 = {0, 680, 900, 40, 0, 0, 0, 0};
    Platform ground2 = {1100, 680, 600, 40, 0, 0, 0, 0};
    Platform ground3 = {1850, 680, 500, 40, 0, 0, 0, 0};
    Platform ground4 = {2950, 680, 900, 40, 0, 0, 0, 0};
    Platform ground5 = {4000, 680, 1300, 40, 0, 0, 0, 0};
    Platform plat1 = {1550, 520, 180, 30, 0, 0, 0, 0};
    Platform plat2 = {1800, 430, 180, 30, 0, 0, 0, 0};
    Platform plat3 = {4100, 500, 180, 30, 0, 0, 0, 0};
    Platform plat4 = {4400, 420, 180, 30, 0, 0, 0, 0};
    Platform plat5 = {4700, 340, 200, 30, 0, 0, 0, 0};
    Platform moving1 = {2350, 500, 250, 30, 1, 4, 2350, 2750};
    Platform moving2 = {4850, 500, 180, 30, 1, 5, 4850, 5250};

    map->plats[0] = ground1;
    map->plats[1] = ground2;
    map->plats[2] = ground3;
    map->plats[3] = ground4;
    map->plats[4] = ground5;
    map->plats[5] = plat1;
    map->plats[6] = plat2;
    map->plats[7] = plat3;
    map->plats[8] = plat4;
    map->plats[9] = plat5;
    map->plats[10] = moving1;
    map->plats[11] = moving2;
    map->n_plats = 12;
    
    map->enemies[0] = createEnemy(sprite, 250, 630, 150, 750, E_WALK);
    map->enemies[1] = createEnemy(sprite, 1350, 630, 1200, 1600, E_WALK);
    map->enemies[2] = createEnemy(sprite, 3450, 630, 3100, 3750, E_WALK);
    map->enemies[3] = createEnemy(sprite, 1800, 380, 1800, 1800, E_JUMP);
    map->enemies[4] = createEnemy(sprite, 2500, 450, 2600, 2600, E_JUMP);
    map->enemies[5] = createEnemy(sprite, 4450, 370, 4450, 4450, E_JUMP);
    map->n_enemies = 6;

    Platform pit1 = {900, 680, 200, 40, 0, 0, 0, 0};
    Platform pit2 = {1700, 680, 150, 40, 0, 0, 0, 0};
    Platform pit3 = {2350, 680, 600, 40, 0, 0, 0, 0};
    Platform pit4 = {3850, 680, 150, 40, 0, 0, 0, 0};
    Platform pit5 = {5300, 680, 1000, 40, 0, 0, 0, 0};

    map->pits[0] = pit1;
    map->pits[1] = pit2;
    map->pits[2] = pit3;
    map->pits[3] = pit4;
    map->pits[4] = pit5;
    map->n_pits = 5;

    map->spikes[0] = createSpike(1250,640,64,64);
    map->spikes[1] = createSpike(3150,616,64,64);
    map->spikes[2] = createSpike(3300,616,64,64);
    map->spikes[3] = createSpike(3450,616,64,64);
    map->spikes[4] = createSpike(3600,616,64,64);
    map->spikes[5] = createSpike(4550,616,64,64);
    map->spikes[6] = createSpike(4625,616,64,64);
    map->n_spikes = 7;

    map->gases[0] = createGas(1600, 550, 350, 130);
    map->gases[1] = createGas(4050, 550, 500, 130);
    map->n_gases = 2;

    map->omnitrix.pos_x = 5300;
    map->omnitrix.pos_y = 500;
    map->omnitrix.width = 45;
    map->omnitrix.height = 45;

    return 0;
}

void updateEnemy(Map *map){
    Enemy *enemy;
    const float walk_speed = 2.0f;
    const int pause_frames = 20;
    const float jump = -12.0f;
    const float gravity = 0.5f;
    int i;

    if(map->n_enemies <= 0)
        return;

    for(i = 0; i < map->n_enemies; i++){
        enemy = &map->enemies[i];

        if(enemy->state == E_IDLE){
            enemy->vx = 0;
            enemy->vy = 0;
            enemy->curr_frame = 0;
        }
        else if(enemy->state == E_WALK){
            if(enemy->wait_timer > 0){
                enemy->wait_timer--;
                enemy->vx = 0;

                if(enemy->wait_timer == 0)
                    enemy->direction *= -1;
            }
            else{
                enemy->vx = walk_speed * enemy->direction;
                enemy->pos_x += enemy->vx;

                if(enemy->pos_x <= enemy->lim_left){
                    enemy->pos_x = enemy->lim_left;
                    enemy->wait_timer = pause_frames;
                    enemy->vx = 0;
                }
                else if(enemy->pos_x >= enemy->lim_right){
                    enemy->pos_x = enemy->lim_right;
                    enemy->wait_timer = pause_frames;
                    enemy->vx = 0;
                }
            }

            enemy->frame_timer++;
            if(enemy->frame_timer >= 8){
                enemy->frame_timer = 0;
                enemy->curr_frame++;
                if(enemy->curr_frame > 3)
                    enemy->curr_frame = 0;
            }
        }
        else if(enemy->state == E_JUMP){
            if(enemy->wait_timer > 0){
                enemy->wait_timer--;
                if(enemy->wait_timer == 0){
                    enemy->vy = jump;
                }
            }
            else{
                enemy->vy += gravity;
                enemy->pos_y += enemy->vy;

                if(enemy->pos_y >= enemy->start_y){
                    enemy->pos_y = enemy->start_y;
                    enemy->vy = 0;
                    enemy->wait_timer = 30;
                }
            }
            enemy->curr_frame = 0;
        }
    }
}

void updatePlatforms(Map *map){
    int i;

    for(i = 0; i < map->n_plats; i++){
        Platform *p = &map->plats[i];

        if(!p->moving)
            continue;

        p->pos_x += p->vx;

        if(p->pos_x < p->lim_left || p->pos_x + p->width > p->lim_right)
            p->vx *= -1;
    }
}

void drawEnemy(Enemy e, Camera cam){
    int sprite_x;
    int sprite_y;
    int sprite_h = 40;
    int sprite_w;

    
    switch(e.state){
        case E_IDLE:
            sprite_w = 56;
            sprite_x = e.curr_frame * sprite_w;
            sprite_y = 0;
            break;

        case E_WALK:
            sprite_w = 45;
            sprite_x = e.curr_frame * sprite_w;
            sprite_y = 80;
            break;

        case E_JUMP:
                sprite_w = 55;
                sprite_x = 0;
                sprite_y = 40;
    }

    int flag = e.vx < 0 ? ALLEGRO_FLIP_HORIZONTAL : 0;

    float draw_x = e.pos_x - cam.x + (e.width - sprite_w) / 2.0f;
    float draw_y = e.pos_y - cam.y + (e.height - sprite_h);

    al_draw_bitmap_region(
        e.sprite,
        sprite_x,
        sprite_y,
        sprite_w,
        sprite_h,
        draw_x,
        draw_y,
        flag
    );
}

void drawSpike(Spike s, ALLEGRO_BITMAP *sprite, Camera cam){
    al_draw_scaled_bitmap(
        sprite,
        0, 0,
        al_get_bitmap_width(sprite),
        al_get_bitmap_height(sprite),
        s.pos_x - cam.x,
        s.pos_y - cam.y,
        s.width,
        s.height,
        0
    );
}

void drawPlatform(Platform plat, ALLEGRO_BITMAP *sprite, Camera cam){
    al_draw_scaled_bitmap(
        sprite,
        0,
        0,
        al_get_bitmap_width(sprite),
        al_get_bitmap_height(sprite),
        plat.pos_x - cam.x,
        plat.pos_y - cam.y,
        plat.width,
        plat.height,
        0
    );
}

void drawPit(Platform pit, ALLEGRO_BITMAP *sprite, Camera cam){
    al_draw_scaled_bitmap(
        sprite,
        0, 0,
        al_get_bitmap_width(sprite),
        al_get_bitmap_height(sprite),
        pit.pos_x - cam.x,
        pit.pos_y - cam.y,
        pit.width,
        pit.height,
        0
    );
}

void drawGas(Gas gas, Camera cam){
    al_draw_filled_rectangle(
        gas.pos_x - cam.x,
        gas.pos_y - cam.y,
        gas.pos_x + gas.width - cam.x,
        gas.pos_y + gas.height - cam.y,
        al_map_rgba(0, 255, 0, 120)
    );
}

void drawOmnitrix(ALLEGRO_BITMAP *sprite, Map map, Camera cam){
    Omnitrix omni = map.omnitrix;
    al_draw_scaled_bitmap(
        sprite,
        0, 0,
        al_get_bitmap_width(sprite),
         al_get_bitmap_height(sprite),
        omni.pos_x - cam.x,
        omni.pos_y - cam.y,
        omni.width, omni.height,
        0
    );
}