#include "init.h"
#include "Player.h"

void drawHome(ALLEGRO_DISPLAY *disp, ALLEGRO_FONT *font, int selected);

void drawPlatform(Platform plat);

void drawGame(Player p, Platform plat, ALLEGRO_BITMAP *bg);

void handleInput(ALLEGRO_EVENT event, Input *input, int *selected, state *curr_state);
