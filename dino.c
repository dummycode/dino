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

/**
 * Update the dino's state
 */
void dino__update_state(Dino *dino) {
    switch (dino->state) {
        case STATE_STILL:
            // If dino is on the ground, start running!
            if (dino->p.y == GROUND) {
                dino->state = STATE_RIGHT;
            }
            break;
        case STATE_RIGHT:
            dino->state = STATE_LEFT;
            break;
        case STATE_LEFT:
            dino->state = STATE_RIGHT;
            break;
        default:
            break;
    }
}

/**
 * Dino jumped
 */
void dino__jump(Dino *dino) {
    dino->nv = (Vector) {
        .x = 0,
        .y = -1,
    };
}

/**
 * Update a dino's location
 */
void dino__update(Dino *dino) {
    // Get new location
    dino->np.x = dino->p.x + dino->nv.x;
    dino->np.y = dino->p.y + dino->nv.y;

    dino->v = dino->nv;
   
    // Stop once we hit the ground
    if (dino->np.y > GROUND - DINO_HEIGHT) {
        dino->np.y = GROUND - DINO_HEIGHT;
        dino->nv.y = 0;
        dino->state = STATE_RIGHT;
    }

    // Hardcode hitting the top
    if (dino->np.y < 0) {
        dino->np.y = 0;
        dino->nv.y = 1;
    }
}

/**
 * Clear the old dino's drawing
 */
void dino__clear_old(Dino *dino) {
    drawRectangle(dino->p.y, dino->p.x, DINO_HEIGHT, DINO_WIDTH, BACKGROUND_COLOR);
}

/**
 * Draw the dino at its TODO: (current?) location
 */
void dino__draw(Dino *dino) {
    switch (dino->state) {
        case STATE_STILL:
            drawImage(dino->np.y, dino->np.x, DINO_HEIGHT, DINO_WIDTH, dino_still);
            break;
        case STATE_RIGHT:
            drawImage(dino->np.y, dino->np.x, DINO_HEIGHT, DINO_WIDTH, dino_right);
            break;
        case STATE_LEFT:
            drawImage(dino->np.y, dino->np.x, DINO_HEIGHT, DINO_WIDTH, dino_left);
            break;
    }

    // TODO: this may go elsewhere
    dino__next(dino);
}

/**
 * Update dino's values to next values
 */
void dino__next(Dino *dino) {
    dino->p = dino->np;
    dino->v = dino->nv;
}

