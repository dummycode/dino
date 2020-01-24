#ifndef DRAW_H
#define DRAW_H

#include "game.h"

// Prototypes
void drawAppState(AppState *appState);
void undrawAppState(AppState *appState);
void drawGround();
void drawDino(Dino *dino);
void drawScore(uint_t score);
void drawEnemies(Enemy *enemies, uint_t num_enemies);

#endif
