#include "Player.h"

Player createPlayer(){
    Player p;

    p.hp = 100;
    p.pos_x = 30;
    p.pos_y = 600;
    p.vx = 0;
    p.vy = 0;

    return p;
}

void updatePlayer(Player *player, Input input, int hp){
    player->hp -= hp;

    if(input.left)
        player->pos_x -= 5;

    if(input.right)
        player->pos_x += 5;
}

