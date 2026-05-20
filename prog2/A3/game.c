#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>

void Button(ALLEGRO_FONT *font){
    al_draw_rectangle(60, 40, 60, 40, al_map_rgb(255,0,0), 10);
    al_draw_text(font, al_map_rgb(0,0,0), 450, 320, 0, "TESTE");
}

int main(){
    al_init();
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_install_keyboard();
    al_install_mouse();

    ALLEGRO_TIMER *timer = al_create_timer(1.0 / 30);
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();  
    ALLEGRO_DISPLAY *disp = al_create_display(1280, 720);
    ALLEGRO_FONT *font = al_load_ttf_font("assets/fonts/Jersey20-Regular.ttf", 32, 0);
    
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_mouse_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));

    ALLEGRO_EVENT event;
    al_start_timer(timer);
 

    while(1){
        al_wait_for_event(queue, &event);
    
        al_clear_to_color(al_map_rgb(255,255,255));
        if(event.type == 30){
            Button(font);
            al_flip_display();
        }

        else if(event.type == 42)
            break;
    }

    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    al_uninstall_keyboard();
    al_ungrab_mouse();
}