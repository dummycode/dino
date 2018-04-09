#ifndef GAME_H
#define GAME_H

#include "enemy.h"

#include <stdbool.h>

void drawGame(Dino *dino, Enemy enemies[], bool *selectPressed, GameState *state);
void drawScore();
void drawGround();
void resetGame();
void updateEnemies(Enemy *enemies);
void drawEnemies(Enemy *enemies);
bool didLose(Dino *dino, Enemy *enemies);
void updateLocationOfEnemies(Enemy *enemies);
void clearOldEnemies(Enemy *enemies);

extern volatile unsigned short counter;

#endif

