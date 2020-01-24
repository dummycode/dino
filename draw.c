#include <stdio.h>

#include "graphics.h"
#include "enemy.h"
#include "main.h"
#include "text.h"
#include "myLib.h"
#include "colors.h"

#include "img/dino_still.h"
#include "img/dino_left.h"
#include "img/dino_right.h"

#define GROUND 100

#define UNUSED(var) ((void) (var))

void drawAppState(AppState *appState) {
  // Draw ground and clouds
  drawGround();
  
  // Draw dino
  // clearOldDino(dino);
  drawDino(&appState->dino);
  
  // Draw cactuses and (p)terodactyls
  waitForVblank();
  // clearOldEnemies(enemies);
  drawEnemies(appState->enemies, NUM_ENEMIES);

  // Draw score
  drawScore(appState->score);
}


/*
 * Draws the score in the upper right corner of the screen
 */
void drawScore(uint_t score) {
  char buffer[1024];
  sprintf(buffer, "Score: %d", score);
  drawString(4, 170, buffer, TEXT_COLOR, BACKGROUND_COLOR);
}

void drawGround() {
  volatile uint_t source = TEXT_COLOR;
  DMA[3].src = &source;
  DMA[3].dst = &videoBuffer[(OFFSET(GROUND, 0, SCREEN_WIDTH))];
  DMA[3].cnt = SCREEN_WIDTH | DMA_SOURCE_FIXED | DMA_ON;
}

void drawDino(Dino *dino) {
  switch (dino->state) {
    case STATE_STILL:
      drawImage(dino->p.y, dino->p.x, DINO_HEIGHT, DINO_WIDTH, dino_still);
      break;
    case STATE_RIGHT:
      drawImage(dino->p.y, dino->p.x, DINO_HEIGHT, DINO_WIDTH, dino_right);
      break;
    case STATE_LEFT:
      drawImage(dino->p.y, dino->p.x, DINO_HEIGHT, DINO_WIDTH, dino_left);
      break;
  }
}

void drawEnemies(Enemy *enemies, uint_t num_enemies) {
  UNUSED(enemies);
  UNUSED(num_enemies);
}


