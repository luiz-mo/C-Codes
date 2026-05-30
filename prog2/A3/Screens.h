#include "init.h"
#include "Player.h"

void drawHome(ALLEGRO_DISPLAY *disp, ALLEGRO_FONT *font, int selected);

void drawGame(Player p, ALLEGRO_BITMAP *bg);

void handleInput(ALLEGRO_EVENT event, Input *input, int *selected, state *curr_state);
