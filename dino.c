#include "img/dino_still.h"
#include "img/dino_left.h"
#include "img/dino_right.h"
#include "graphics.h"
#include "dino.h"
#include "myLib.h"
#include "colors.h"

#include <stdbool.h>

#define GROUND 100
#define STEP 5

void updateDinoState(Dino *dino) {
  switch (dino->state) {
    case STATE_STILL:
      // If dino is on the ground, start running!
      if (dino->p.y == 0 && dino->v.y == 0) {
        dino->state = STATE_RIGHT;
      }
      break;
    case STATE_RIGHT:
        dino->state = STATE_LEFT;
      break;
    case STATE_LEFT:
        dino->state = STATE_RIGHT;
      break;
  }
}

void updateDino(Dino *dino) {
  // Every 4 ticks, update time in air
  dino->timeInAir += 1;
  int mult = dino->timeInAir / 15;

  dino->np.x = dino->p.x + dino->v.x;
  dino->np.y = dino->p.y + dino->v.y;

  dino->nv.y = dino->v.y + mult;

  if (dino->np.y > GROUND - DINO_HEIGHT) {
    dino->np.y = GROUND - DINO_HEIGHT;
    dino->nv.y = 0;
    dino->state = STATE_RIGHT;
  }
}

void clearOldDino(Dino *dino) {
  drawRectangle(dino->p.y, dino->p.x, DINO_HEIGHT, DINO_WIDTH, BACKGROUND_COLOR);
}

