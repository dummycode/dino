#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#include "enemy.h"

typedef struct {
  // Holds the current app state
  Dino dino;
} AppState;

void drawGame(Dino *dino, Enemy enemies[], uint_t previousButtons, uint_t currentButtons, GameState *state);
void drawScore();
void drawGround();
void resetGame();
void updateEnemies(Enemy *enemies);
void drawEnemies(Enemy *enemies);
bool didLose(Dino *dino, Enemy *enemies);
void updateLocationOfEnemies(Enemy *enemies);
void clearOldEnemies(Enemy *enemies);

extern volatile unsigned int counter;

#endif
