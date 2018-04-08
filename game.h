#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

void drawGame(Dino *dino, bool *selectPressed, GameState *state);
void drawScore();
void drawGround();
void resetGame();
void updateEnemies();
void drawEnemies();
bool didLose(Dino *dino);
void updateLocationOfEnemies();
void clearOldEnemies();

extern volatile unsigned short *pcounter;

#endif

