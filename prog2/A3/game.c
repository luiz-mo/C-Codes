#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

#include "init.h"
#include "Screens.h"

int main(){
    /*inicializacoes necessarias*/
    init();

    Player player = createPlayer();
    Input input = createInput();
    Map map = createMap();

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 30);
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();  
    ALLEGRO_DISPLAY *disp = al_create_display(1280, 720);
    ALLEGRO_BITMAP *sprite = al_load_bitmap("./assets/images/sprite_run.png");
    ALLEGRO_FONT *font = al_load_ttf_font("./assets/fonts/Jersey20-Regular.ttf", 32, 0);
    ALLEGRO_BITMAP *bg = al_load_bitmap("./assets/images/PNG/game_background_1/game_background_1.png");
    
    if(!sprite){
        printf("Erro ao carregar sprite\n");
        return 1;
    }

    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    ALLEGRO_EVENT event;
    al_start_timer(timer);
 
    al_clear_to_color(al_map_rgb(255,255,255));
    
    int selected = 0;
    int bg_x = 0;
    state curr_state = HOME;

    while(1){
        al_wait_for_event(queue, &event);

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE || curr_state == EXIT)
            break;
        
        handleInput(event, &input, &selected, &curr_state, disp, font);

        if(event.type == ALLEGRO_EVENT_TIMER){
            if(curr_state == HOME){
                drawHome(disp, font, selected);
                al_flip_display();
            }

            else if(curr_state == RUNNING){
                updatePlayer(&player, input, map, 100);
                
                if(input.right)
                    bg_x -= 2;
                if(bg_x < -al_get_bitmap_width(bg))
                    bg_x = 0;

                drawGame(player, map, bg, bg_x);
                al_flip_display();
            }
            else if(curr_state == PAUSED){
                drawGame(player, map, bg, bg_x);
                drawPausedScreen(disp, font);
                al_flip_display();
            }
        }

    }

    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_bitmap(sprite);

    al_uninstall_keyboard();
    al_uninstall_mouse();

    return 0;
}