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
    else
        player->vx = 0;

    if(input.right)
        player->vx = 10;
    else
        player->vx = 0;

    if(input.jump && player->on_ground){
        player->vy = -17;
        player->on_ground = 0;
    }

    if(input.crouch){
        if(player->height == DEFAULT_HEIGHT){
            player->pos_y += CROUCH;
            player->height -= CROUCH;
        }
    }
    else{
        if(player->height != DEFAULT_HEIGHT){
            player->pos_y -= CROUCH;
            player->height = DEFAULT_HEIGHT;

            /*verifica se tem espaco para uncrouch*/
            if(checkCollision(player, map) != -1){
                player->pos_y += CROUCH;
                player->height -= CROUCH;
            }
        }
    }

    player->vy += GRAVITY;

    /*guarda posicao antiga para checar colisoes*/
    float prev_y = player->pos_y;
    float prev_x = player->pos_x;

    player->pos_x += player->vx;

    int coll_id = checkCollision(player, map);
    if(coll_id != -1){
        Platform plat = map.plats[coll_id];
        /*colidiu pela esquerda*/
        if(prev_x + player->width <= plat.pos_x){
            player->pos_x = plat.pos_x - player->width;
        }
        /*colidiu pela direita*/
        else if(prev_x >= plat.pos_x + plat.width){
            player->pos_x = plat.pos_x + plat.width;
        }

        player->vx = 0;
    }

    player->pos_y += player->vy;

    if(player->pos_y > map.plats[0].pos_y + map.plats[0].height){
        player->hp = 0;
        return;
    }

    coll_id = checkCollision(player, map);
    if(coll_id != -1){
        Platform plat = map.plats[coll_id];
        if(prev_y + player->height <= plat.pos_y){
            /*caiu no topo da plat*/
            player->pos_y = plat.pos_y - player->height;
            player->vy = 0;
            player->on_ground = 1;
        }
        else if(prev_y >= plat.pos_y + plat.height){
            /*bateu a cabeca*/
            player->pos_y = plat.pos_y + plat.height;
            player->vy = 0;
        }
    }


}

