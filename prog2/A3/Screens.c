#include "Screens.h"

void drawHome(ALLEGRO_DISPLAY *disp, ALLEGRO_FONT *font, int selected){
    int pos_x = al_get_display_width(disp)/2;
    ALLEGRO_COLOR color0, color1;

    color0 = selected == 0 ? al_map_rgb(255,255,0) : al_map_rgb(255,255,255);
    color1 = selected == 1 ? al_map_rgb(255,255,0) : al_map_rgb(255,255,255);

    al_clear_to_color(al_map_rgb(0,0,255));
    al_draw_text(
        font, color0, pos_x,
        al_get_display_height(disp)/ 3, ALLEGRO_ALIGN_CENTER, "JOGAR");

    al_draw_text(
        font, color1, pos_x,
        al_get_display_height(disp)/2, ALLEGRO_ALIGN_CENTER, "SAIR DO JOGO");
    
    al_flip_display();
}

void drawGame(Player p, ALLEGRO_BITMAP *bg){
    al_draw_bitmap(bg, 0, 0, 0);
    al_draw_rectangle(10, 15, 10, 15, al_map_rgb(255, 0, 0), 10);

    if(p.hp == 10)
        return;

    al_flip_display();
}

void handleMovement(ALLEGRO_EVENT event){
    switch(event.keyboard.keycode){
        case ALLEGRO_KEY_RIGHT:

    }
}

void handleInput(ALLEGRO_EVENT event, int *selected, state *curr_state){
    if(*curr_state == HOME){
        switch(event.keyboard.keycode){
            case ALLEGRO_KEY_DOWN:
                (*selected)++;
                
                if(*selected > 1)
                    *selected = 0; 
                break;
            
            case ALLEGRO_KEY_UP:
                (*selected)--;

                if(*selected < 0)
                    *selected = 1;
                break;
            
            case ALLEGRO_KEY_ENTER:
                if(*selected == 0)
                    *curr_state = RUNNING;
                else if(*selected == 1)
                    *curr_state = EXIT;
        }
    }

    else if(*curr_state == RUNNING){

    }
}