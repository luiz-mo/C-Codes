#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>

#include "Screens.h"

int main(){
    /*inicializacoes necessarias*/
    al_init();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    al_install_keyboard();
    al_install_mouse();

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

    //float frame = 0;
    //int pos_x = 0, pos_y = 0;
    //int current_frame_y = 161;

    enum state{
        HOME,
        RUNNING,
        PAUSED,
        Z
    };

    enum state curr_state = HOME;
    enum state prev_state = Z;

    while(1){
        al_wait_for_event(queue, &event);

        if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            break;
        
        if(event.type == ALLEGRO_EVENT_KEY_DOWN)
            if(curr_state == HOME)
                curr_state = RUNNING;

        if(event.type == ALLEGRO_EVENT_TIMER){
            if(curr_state == HOME){
                if(curr_state != prev_state)
                    drawHome(font, disp);
                
                prev_state = HOME;
            }

            else if(curr_state == RUNNING){
                if(curr_state != prev_state){
                    al_draw_bitmap(bg, 0, 0, 0);
                    al_flip_display();
                }
            }
        }

    }

    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    al_destroy_bitmap(sprite);

    al_uninstall_keyboard();
    al_uninstall_mouse();
}