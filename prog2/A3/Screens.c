#include "Screens.h"

void confirmationPopup(ALLEGRO_FONT *font, ALLEGRO_DISPLAY *disp){
    int width = al_get_display_width(disp);
    int height = al_get_display_height(disp);

    int x1 = width/2 - 400;
    int y1 = height/2 - 150;
    int x2 = x1 + 800;
    int y2 = y1 + 300;

    al_draw_filled_rectangle(x1, y1, x2, y2, al_map_rgb(0, 0, 0));

    al_draw_rectangle(x1, y1, x2, y2, al_map_rgb(255,255,255), 3);

    al_draw_text(
        font,
        al_map_rgb(255,255,255),
        width/2,
        height/2 - 20,
        ALLEGRO_ALIGN_CENTER,
        "Tem certeza que quer sair? Seu progresso será salvo"
    );

    al_draw_text(
        font,
        al_map_rgb(200,200,200),
        width/2,
        height/2 + 20,
        ALLEGRO_ALIGN_CENTER,
        "Pressione Enter para confirmar"
    );
}

void updateBackground(Input input, ALLEGRO_BITMAP *bg, int *bg_x){
    if(input.right)
        *bg_x -= 2;
    else if(input.left)
        *bg_x += 2;

    if(*bg_x > 0)
        *bg_x = 0;

    if(*bg_x < -al_get_bitmap_width(bg))
        *bg_x = 0;
}

void drawHome(ALLEGRO_DISPLAY *disp, ALLEGRO_FONT *font, ALLEGRO_BITMAP *bg, int selected){
    int width = al_get_display_width(disp);
    int height = al_get_display_height(disp);
    ALLEGRO_COLOR color0, color1;

    color0 = selected == 0 ? al_map_rgb(255,0,0) : al_map_rgb(255,255,255);
    color1 = selected == 1 ? al_map_rgb(255,0,0) : al_map_rgb(255,255,255);

    //al_clear_to_color(al_map_rgb(0,0,255));
    al_draw_bitmap(bg, 0, 0 ,0);
    al_draw_text(
        font,
        color0,
        width/2,
        height/3,
        ALLEGRO_ALIGN_CENTER,
        "JOGAR");

    al_draw_text(
        font,
        color1,
        width/2,
        height/2,
        ALLEGRO_ALIGN_CENTER,
        "SAIR DO JOGO");
}

void drawPausedScreen(ALLEGRO_DISPLAY *disp, ALLEGRO_FONT *font){
    int width = al_get_display_width(disp);
    int height = al_get_display_height(disp);

    al_draw_filled_rectangle(
        0,
        0,
        width,
        height,
        al_map_rgba(0, 0, 0, 128)
        );

    al_draw_text(
        font,
        al_map_rgb(255, 255, 255),
        width/2,
        height/3,
        ALLEGRO_ALIGN_CENTER,
        "PAUSADO");

    al_draw_text(
        font,
        al_map_rgb(255, 255, 255),
        width/2,
        height/2,
        ALLEGRO_ALIGN_CENTER,
        "Pressione Esc para continuar ou s para sair"
    );
}

void drawPlatform(Platform plat, Camera cam){
    al_draw_filled_rectangle(
        plat.pos_x - cam.x,
        plat.pos_y - cam.y,
        plat.pos_x + plat.width - cam.x,
        plat.pos_y + plat.height - cam.y,
        al_map_rgb(255, 255, 255)
    );
}

void drawGame(Player p, Map map, ALLEGRO_BITMAP *bg, int bg_x, Camera cam){
    /*desenha background*/
    int bg_w = al_get_bitmap_width(bg);

    al_draw_bitmap(bg, bg_x, 0, 0);
    al_draw_bitmap(bg, bg_x + bg_w, 0, 0);
    
    /*desenha plataformas*/
    int i;
    for(i=0;i < map.n_plats;i++)
        drawPlatform(map.plats[i], cam);

    /*desenha o jogador*/
    drawPlayer(p, cam);

    drawEnemy(map, cam);

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

}

void drawGameOver(ALLEGRO_DISPLAY *disp, ALLEGRO_FONT *font){
    int width = al_get_display_width(disp);
    int height = al_get_display_height(disp);

    al_draw_filled_rectangle(0, 0, width, height, al_map_rgb(0, 0, 0));
    al_draw_text(font, al_map_rgb(255, 255, 0), width/2, height/2, ALLEGRO_ALIGN_CENTER, "GAME OVER");
}

void handleInput(ALLEGRO_EVENT event, Input *input, int *selected, state *curr_state, ALLEGRO_DISPLAY *d, ALLEGRO_FONT *f){
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
                    break;

                case ALLEGRO_KEY_ESCAPE:
                    *curr_state = PAUSED;
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

    else if(*curr_state == PAUSED){
        if(event.type == ALLEGRO_EVENT_KEY_DOWN){
            switch(event.keyboard.keycode){
                case ALLEGRO_KEY_ESCAPE:
                    input->crouch = 0;
                    input->jump = 0;
                    input->left = 0;
                    input->right = 0;
                    *curr_state = RUNNING;

                    break;

                case ALLEGRO_KEY_S:
                    confirmationPopup(f,d);
                    *curr_state = CONFIRM;
                    al_flip_display();
            }
        }
    }

    else if(*curr_state == CONFIRM){
        if(event.type == ALLEGRO_EVENT_KEY_DOWN){
            switch(event.keyboard.keycode){
                case ALLEGRO_KEY_ESCAPE:
                    *curr_state = PAUSED;
                    break;

                case ALLEGRO_KEY_ENTER:
                    input->crouch = 0;
                    input->jump = 0;
                    input->left = 0;
                    input->right = 0;
                    *curr_state = HOME;
            }
        }
    }

    else if(*curr_state == GAME_OVER){
        if(event.type == ALLEGRO_EVENT_KEY_DOWN){
            switch(event.keyboard.keycode){
                case ALLEGRO_KEY_ENTER:
                    *curr_state = HOME;
            }
        }
    }
}