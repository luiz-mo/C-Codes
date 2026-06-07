#include "init.h"
#include "Player.h"

void drawHome(ALLEGRO_DISPLAY *disp, ALLEGRO_FONT *font, int selected);

void drawPausedScreen(ALLEGRO_DISPLAY *disp, ALLEGRO_FONT *font);

void drawPlatform(Platform plat);

void drawGame(Player p, Map map, ALLEGRO_BITMAP *bg, int bg_x);

void handleInput(ALLEGRO_EVENT event, Input *input, int *selected, state *curr_state, ALLEGRO_DISPLAY *d, ALLEGRO_FONT *f);
