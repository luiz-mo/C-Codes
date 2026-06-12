#include "init.h"
#include "Player.h"
#include "Map.h"

void drawHome(ALLEGRO_DISPLAY *disp, ALLEGRO_FONT *font, ALLEGRO_BITMAP *bg, int selected);

void drawPausedScreen(ALLEGRO_DISPLAY *disp, ALLEGRO_FONT *font);

void drawGame(
            Player p, Map map,
            ALLEGRO_BITMAP *bg, ALLEGRO_BITMAP *plats, ALLEGRO_BITMAP *water,
            ALLEGRO_BITMAP *spikes, ALLEGRO_BITMAP *omni, Camera cam);

void drawGameOver(ALLEGRO_DISPLAY *disp, ALLEGRO_FONT *font);

void drawGameWon(ALLEGRO_DISPLAY *disp, ALLEGRO_FONT *font);

void handleInput(
                ALLEGRO_EVENT event, Input *input, int *selected,
                state *curr_state, ALLEGRO_DISPLAY *d, ALLEGRO_FONT *f);
