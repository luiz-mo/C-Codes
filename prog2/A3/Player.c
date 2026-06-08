#include "Player.h"

Player createPlayer(){
    Player p;

    p.hp = 100;
    p.pos_x = 30;
    p.pos_y = 600;
    p.vx = 0;
    p.vy = 0;
    p.height = 80;
    p.width = 50;
    p.on_ground = 1;

    return p;
}

int checkCollision(Player *p, Map map){
    for(int i = 0; i < map.n_plats; i++){
        Platform plat = map.plats[i];
        if(
            p->pos_x < plat.pos_x + plat.width &&
            p->pos_x + p->width > plat.pos_x &&
            p->pos_y - p->height < plat.pos_y + plat.height &&
            p->pos_y > plat.pos_y
        ){
            return i;
        }
    }

    return -1;
}

void updatePlayer(Player *player, Input input, Map map){
    if(input.left)
        player->vx = -10;

    if(input.right)
        player->vx = 10;

    if(input.jump && player->on_ground){
        player->vy = -15;
        player->on_ground = 0;
    }

    player->vy += GRAVITY;

    player->pos_x += player->vx;
    player->pos_y += player->vy;

    player->vx = 0;

    if(player->pos_y - player->height > map.plats[0].pos_y){
        player->hp = 0;
        return;
    }

    int coll = checkCollision(player, map);

    if(coll == -1)
        return;

    player->pos_y = map.plats[coll].pos_y;
    player->vy = 0;
    player->on_ground = 1;
}

