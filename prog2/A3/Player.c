#include "Player.h"

#define DEFAULT_HEIGHT 60
#define CROUCH_DIFF 15

typedef struct{
    int x;
    int y;
    int w;
    int h;
} Frame;

Player createPlayer(){
    Player p;

    p.sprites = al_load_bitmap("./assets/images/ben10sprites.png");
    p.hp = 100;
    p.pos_x = 30;
    p.pos_y = 450;
    p.vx = 0;
    p.vy = 0;
    p.height = 60;
    p.width = 25;
    p.on_ground = 1;
    p.state = IDLE;
    p.curr_frame = 0;
    p.frame_timer = 0;

    return p;
}

void drawPlayer(Player player, Camera cam){
    int sprite_x, sprite_y, sprite_w, sprite_h;
    
    switch(player.state){
        case RUN:
            Frame run_frames[8] = {
                {18, 82, 31, 46},
                {58, 81, 41, 44},
                {102, 82, 40, 45},
                {150, 82, 32, 45},
                {188, 83, 33, 44},
                {228, 80, 39, 45},
                {273, 81, 38, 46},
                {321, 82, 30, 46}
            };
            
            Frame f = run_frames[player.curr_frame];

            sprite_x = f.x;
            sprite_y = f.y;
            sprite_w = f.w;
            sprite_h = f.h;

            break;

        case CROUCH:
            sprite_x = 16;
            sprite_y = 167;
            sprite_w = 34;
            sprite_h = 34;

            break;

        case JUMP:
            sprite_x = 72;
            sprite_y = 151;
            sprite_w = 39;
            sprite_h = 50;

            break;

        case FALL:
            sprite_x = 12;
            sprite_y = 288;
            sprite_w = 34;
            sprite_h = 34;

            break;

        case IDLE:
            sprite_x = 214;
            sprite_y = 5;
            sprite_w = 21;
            sprite_h = 60;
    }

    float draw_x = player.pos_x - cam.x + (player.width - sprite_w) / 2.0f;
    float draw_y = player.pos_y - cam.y + (player.height - sprite_h);

    al_draw_bitmap_region(
        player.sprites,
        sprite_x, sprite_y,
        sprite_w, sprite_h,
        draw_x, draw_y,
        0);
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

void updatePlayerState(Player *player){
    if(player->height != DEFAULT_HEIGHT)
        player->state = CROUCH;
    else if(!player->on_ground && player->vy < 0)
        player->state = JUMP;
    else if(!player->on_ground)
        player->state = FALL;
    else if(player->vx != 0)
        player->state = RUN;
    else
        player->state = IDLE;
    
}

void updatePlayer(Player *player, Input input, Map map){
    if(input.left)
        player->vx = -10;
    else if(input.right)
        player->vx = 10;
    else
        player->vx = 0;

    if(input.jump && player->on_ground){
        player->vy = -17;
        player->on_ground = 0;
    }

    if(input.crouch){
        if(player->height == DEFAULT_HEIGHT){
            player->pos_y += CROUCH_DIFF;
            player->height -= CROUCH_DIFF;
        }
    }
    else{
        if(player->height != DEFAULT_HEIGHT){
            player->pos_y -= CROUCH_DIFF;
            player->height = DEFAULT_HEIGHT;

            /*verifica se tem espaco para uncrouch*/
            if(checkCollision(player, map) != -1){
                player->pos_y += CROUCH_DIFF;
                player->height -= CROUCH_DIFF;
            }
        }
    }

    player->vy += GRAVITY;

    /*guarda posicao antiga para checar colisoes*/
    float prev_y = player->pos_y;
    float prev_x = player->pos_x;

    player->pos_x += player->vx;

    if(player->pos_x < map.plats[0].pos_x)
        player->pos_x = map.plats[0].pos_x;

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

    player->on_ground = 0;
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

    updatePlayerState(player);

    if(player->state == RUN){
    player->frame_timer++;

    if(player->frame_timer >= 4){
        player->frame_timer = 0;

        player->curr_frame++;

        if(player->curr_frame >= 8)
            player->curr_frame = 0;
    }
    }

    else
    player->curr_frame = 0;
    
}

