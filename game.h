#ifndef GAME_H
#define GAME_H

#include <stdbool.h>

#include "types.h"
#include "enemy.h"


#define NUM_ENEMIES 2

// Holds the current app state
typedef struct {
  Dino dino;
  Enemy enemies[NUM_ENEMIES];
  uint_t score;
  uint_t tick;
} AppState;

AppState initialAppState();
void resetAppState(AppState *appState);
void updateAppState(AppState *appState, uint_t previousButtons, uint_t currentButtons); 

// void drawGame(Dino *dino, Enemy enemies[], uint_t previousButtons, uint_t currentButtons);
// void drawScore();
// void drawGround();
void resetGame();
void updateEnemies(Enemy *enemies);
// void drawEnemies(Enemy *enemies);
bool didLose(Dino *dino, Enemy *enemies);
Enemy getRandomEnemy();
void updateLocationOfEnemies(Enemy *enemies);
// void clearOldEnemies(Enemy *enemies);

extern volatile unsigned int counter;

#endif
