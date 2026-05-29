#include "init.h"
#include "Player.h"

void drawHome(ALLEGRO_DISPLAY *disp, ALLEGRO_FONT *font, int selected);

void drawGame(Player p, ALLEGRO_BITMAP *bg);

void handleMovement(ALLEGRO_EVENT event);

void handleInput(ALLEGRO_EVENT event, int *selected, state *curr_state);
