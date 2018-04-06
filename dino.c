#include "img/dino_still.h"
#include "img/dino_left.h"
#include "img/dino_right.h"
#include "graphics.h"
#include "dino.h"
#include "myLib.h"
#include "colors.h"

#include <stdbool.h>

#define STEP 5
#define GROUND 75

void updateDinoState(Dino *dino)
{   
    switch (dino->state) {
        case STATE_STILL:
            if (dino->p.y == 0 && dino->v.y == 0) {
                dino->state = STATE_RIGHT;
            } else {
            }
            break;
        case STATE_RIGHT:
            if (dino->feet.right < STEP) {
                dino->feet.right += 1;
            } else {
                dino->feet.right = 0;
                dino->state = STATE_LEFT;
            }
            break;
        case STATE_LEFT:
            if (dino->feet.left < STEP) {
                dino->feet.left += 1;
            } else {
                dino->feet.left = 0;
                dino->state = STATE_RIGHT;
            }
            break;
    }     
}

void drawDino(Dino *dino) 
{
    switch (dino->state) {
        case STATE_STILL:
            drawImage(GROUND - dino->p.y, dino->p.x, DINO_HEIGHT, DINO_WIDTH, dino_still);
            break;
        case STATE_RIGHT:
            drawImage(GROUND - dino->p.y, dino->p.x, DINO_HEIGHT, DINO_WIDTH, dino_right);
            break;
        case STATE_LEFT:
            drawImage(GROUND - dino->p.y, dino->p.x, DINO_HEIGHT, DINO_WIDTH, dino_left);
            break;
    } 
}

void updateDino(Dino *dino) 
{
    // Every 4 ticks, update time in air
    if (*pcounter % 4 == 0) {
        dino->timeInAir += 1;
    }
    dino->np.y = dino->p.y + dino->v.y;
    dino->nv.y = dino->v.y - dino->timeInAir;
    
    if (dino->np.y < 0) {
        dino->np.y = 0;
        dino->nv.y = 0;
    }
}

void clearOldDino(Dino *dino)
{
    drawRectangle(GROUND - dino->p.y, dino->p.x, DINO_HEIGHT, DINO_WIDTH, BACKGROUND_COLOR);
}

