#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

void drawGame(Dino *dino, bool *selectPressed, GameState *state);
void drawScore(int *score);
void drawGround();

#endif

