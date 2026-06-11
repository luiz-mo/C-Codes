#include "init.h"
#include "Player.h"
#include "Map.h"

void updateBackground(Input input, ALLEGRO_BITMAP *bg, int *bg_x);

void drawHome(ALLEGRO_DISPLAY *disp, ALLEGRO_FONT *font, ALLEGRO_BITMAP *bg, int selected);

void drawPausedScreen(ALLEGRO_DISPLAY *disp, ALLEGRO_FONT *font);

void drawEnemy(Map map, Camera cam);

void drawGame(Player p, Map map, ALLEGRO_BITMAP *bg, int bg_x, Camera cam);

void drawGameOver(ALLEGRO_DISPLAY *disp, ALLEGRO_FONT *font);

void handleInput(ALLEGRO_EVENT event, Input *input, int *selected, state *curr_state, ALLEGRO_DISPLAY *d, ALLEGRO_FONT *f);
