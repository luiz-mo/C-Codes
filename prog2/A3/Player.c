#include "Player.h"

#define DEFAULT_HEIGHT 80
#define CROUCH 20

Player createPlayer(){
    Player p;

    p.hp = 100;
    p.pos_x = 30;
    p.pos_y = 450;
    p.vx = 0;
    p.vy = 0;
    p.height = 80;
    p.width = 50;
    p.on_ground = 1;
    p.state = IDLE;

    return p;
}

int checkCollision(Player *p, Map map){ 
    for(int i = 0; i < map.n_plats; i++){
        Platform plat = map.plats[i];
        if(
            p->pos_x < plat.pos_x + plat.width &&
            p->pos_x + p->width > plat.pos_x &&
            p->pos_y < plat.pos_y + plat.height &&
            p->pos_y + p->height > plat.pos_y
        )
            return i;
    }

    return -1;
}

void updatePlayer(Player *player, Input input, Map map){
    if(input.left)
        player->vx = -10;

    if(input.right)
        player->vx = 10;

    if(input.jump && player->on_ground){
        player->vy = -17;
        player->on_ground = 0;
    }

    /* handle crouch: apply change only on transition */
    if(input.crouch){
        if(player->height == DEFAULT_HEIGHT){
            player->pos_y += CROUCH; /* move down since pos_y is top */
            player->height -= CROUCH;
        }
    }
    else{
        if(player->height != DEFAULT_HEIGHT){
            player->pos_y -= CROUCH; /* move up to restore */
            player->height = DEFAULT_HEIGHT;
        }
    }

    player->vy += GRAVITY;

    float prev_y = player->pos_y;

    player->pos_x += player->vx;
    player->pos_y += player->vy;

    player->vx = 0;

    if(player->pos_y > map.plats[0].pos_y + map.plats[0].height){
        player->hp = 0;
        return;
    }

    int coll_id = checkCollision(player, map);

    if(coll_id == -1)
        return;

    Platform plat = map.plats[coll_id];

    /*se estava acima da plat e colidiu, entao veio de cima*/
    if(prev_y + player->height <= plat.pos_y){
        player->pos_y = plat.pos_y - player->height;
        player->vy = 0;
        player->on_ground = 1;
    }


}

