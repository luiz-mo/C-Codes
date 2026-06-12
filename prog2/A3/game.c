#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

#include "init.h"
#include "Screens.h"

void resetGame(Player *player, Input *input){
    player->hp = 100;
    player->pos_x = 30;
    player->pos_y = 450;
    player->vx = 0;
    player->vy = 0;
    player->on_ground = 1;

    input->crouch = 0;
    input->jump = 0;
    input->right = 0;
    input->left = 0;
}

int main(){
    /*inicializacoes necessarias*/
    initAddons();

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 30);
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();  
    ALLEGRO_DISPLAY *disp = al_create_display(1280, 720);
    ALLEGRO_FONT *font = al_load_ttf_font("./assets/fonts/Jersey20-Regular.ttf", 32, 0);
    ALLEGRO_BITMAP *bg_home = al_load_bitmap("./assets/images/ben_backgroundd.jpg");
    ALLEGRO_BITMAP *bg = al_load_bitmap("./assets/images/background.jpeg");
    ALLEGRO_BITMAP *enemy = al_load_bitmap("./assets/images/dnalien_sprite.png");
    ALLEGRO_BITMAP *spikes = al_load_bitmap("./assets/images/spike.png");
    ALLEGRO_BITMAP *water = al_load_bitmap("./assets/images/water.png");    
    ALLEGRO_BITMAP *plats = al_load_bitmap("./assets/images/platforms.png");
    ALLEGRO_BITMAP *omni = al_load_bitmap("./assets/images/omnitrix.png");

    al_set_window_title(disp, "omni");

    if(!bg){
        printf("Erro ao carregar background\n");
        return 1;
    }

    Player player = createPlayer();
    Input input = createInput();
    Map map;
    if(createMap(&map, enemy) != 0){
        printf("Erro ao alocar inimigos");
        return 1;
    }
    Camera cam = createCamera();

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    ALLEGRO_EVENT event;
    al_start_timer(timer);
 
    al_clear_to_color(al_map_rgb(255,255,255));
    
    int selected = 0;
    state curr_state = HOME;

    /*laco principal do jogo*/
    while(1){
        al_wait_for_event(queue, &event);

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE || curr_state == EXIT)
            break;
        
        handleInput(event, &input, &selected, &curr_state, disp, font);

        if(event.type == ALLEGRO_EVENT_TIMER){
            if(curr_state == HOME){
                drawHome(disp, font, bg_home, selected);
                al_flip_display();
            }

            else if(curr_state == RUNNING){
                updatePlatforms(&map);
                updatePlayer(&player, input, map);
                updateEnemy(&map);

                if(player.won){
                    curr_state = GAME_WON;
                    continue;
                }

                else if(player.hp <= 0){
                    curr_state = GAME_OVER;
                    continue;
                }

                cam.x = player.pos_x - al_get_display_width(disp)/2;
                if(cam.x < 0)
                    cam.x = 0;

                drawGame(player, map, bg, plats, water, spikes, omni, cam);
                al_flip_display();
            }
            else if(curr_state == PAUSED){
                drawGame(player, map, bg, plats, water, spikes, omni, cam);
                drawPausedScreen(disp, font);
                al_flip_display();
            }
            else if(curr_state == GAME_OVER){
                drawGameOver(disp,font);
                resetGame(&player, &input);
                al_flip_display();
            }
            else if(curr_state == GAME_WON){
                drawGameWon(disp, font);
                resetGame(&player, &input);
                al_flip_display();
            }
        }
    }

    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_bitmap(player.sprites);
    al_destroy_bitmap(bg);
    al_destroy_bitmap(bg_home);
    al_destroy_bitmap(enemy);
    al_destroy_bitmap(spikes);
    al_destroy_bitmap(water);
    al_destroy_bitmap(plats);
    al_destroy_font(font);

    al_uninstall_keyboard();

    return 0;
}