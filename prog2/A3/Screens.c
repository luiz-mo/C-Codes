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


void drawPlatform(Platform plat){
    al_draw_filled_rectangle(
        plat.pos_x,
        plat.pos_y, 
        plat.pos_x + plat.width,
        plat.pos_y + plat.height,
        al_map_rgb(255, 255, 255)
    );
}

void drawGame(Player p, Platform plat, ALLEGRO_BITMAP *bg){
    al_draw_bitmap(bg, 0, 0, 0);
    
    /*desenha plataformas*/
    drawPlatform(plat);

    /*desenha o jogador*/
    al_draw_rectangle(p.pos_x, p.pos_y, p.pos_x + 50, p.pos_y - 80, al_map_rgb(255, 0, 0), 5);

    /*desenha barra de vida*/
    int x = 50;
    int y = 50;
    float bar_w = 200;
    float bar_h = 30;
    float hp_w = bar_w * ((float)p.hp / 100);

    /*fundo da barra*/
    al_draw_filled_rectangle(x, y, x+bar_w, y+bar_h, al_map_rgb(50, 50, 50));
    /*hp*/
    al_draw_filled_rectangle(x, y, x+hp_w, y+bar_h, al_map_rgb(255, 0, 0));

    al_flip_display();
}

void handleInput(ALLEGRO_EVENT event, Input *input, int *selected, state *curr_state){
    if(*curr_state == HOME){
        if(event.type == ALLEGRO_EVENT_KEY_DOWN)
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
        if(event.type == ALLEGRO_EVENT_KEY_DOWN)
            switch(event.keyboard.keycode){
                case ALLEGRO_KEY_DOWN:
                    input->crouch = 1;
                    break;

                case ALLEGRO_KEY_LEFT:
                    input->left = 1;
                    break;

                case ALLEGRO_KEY_UP:
                    input->jump = 1;
                    break;

                case ALLEGRO_KEY_RIGHT:
                    input->right = 1;
            }
        else if(event.type == ALLEGRO_EVENT_KEY_UP)
            switch(event.keyboard.keycode){
                case ALLEGRO_KEY_DOWN:
                    input->crouch = 0;
                    break;

                case ALLEGRO_KEY_LEFT:
                    input->left = 0;
                    break;

                case ALLEGRO_KEY_UP:
                    input->jump = 0;
                    break;

                case ALLEGRO_KEY_RIGHT:
                    input->right = 0;
            }
    }
}