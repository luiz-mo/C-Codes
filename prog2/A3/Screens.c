#include <allegro5/allegro5.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>

void drawHome(ALLEGRO_FONT *font, ALLEGRO_DISPLAY *disp){
    int pos_x = al_get_display_width(disp)/2;

    al_clear_to_color(al_map_rgb(0,0,255));
    al_draw_text(
        font, al_map_rgb(255,255,255), pos_x,
        al_get_display_height(disp)/ 3, 0, "JOGAR");
    al_draw_text(
        font, al_map_rgb(255,255,255), pos_x,
        al_get_display_height(disp)/2, 0, "SAIR DO JOGO");
    
    al_flip_display();
}

//void handleHome(ALLEGRO_FONT *font, ALLEGRO_DISPLAY )