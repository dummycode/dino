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

void drawDino(Dino *dino)
{   
    switch (dino->state) {
        case STATE_STILL:
            if (dino->loc.y == 0 && dino->vel.y == 0) {
                dino->state = STATE_RIGHT;
            } else {
                drawImage(GROUND - dino->loc.y, dino->loc.x, DINO_STILL_HEIGHT, DINO_STILL_WIDTH, dino_still);
            }
            break;
        case STATE_RIGHT:
            if (dino->feet.right < STEP) {
                dino->feet.right += 1;
                drawImage(GROUND - dino->loc.y, dino->loc.x, DINO_RIGHT_HEIGHT, DINO_RIGHT_WIDTH, dino_right);
            } else {
                dino->feet.right = 0;
                dino->state = STATE_LEFT;
            }
            break;
        case STATE_LEFT:
            if (dino->feet.left < STEP) {
                dino->feet.left += 1;
                drawImage(GROUND - dino->loc.y, dino->loc.x, DINO_LEFT_HEIGHT, DINO_LEFT_WIDTH, dino_left);
            } else {
                dino->feet.left = 0;
                dino->state = STATE_RIGHT;
            }
            break;
    }
}

void updateDino(Dino *dino) {
    if (dino->lastUpdated < 3) {
        dino->lastUpdated += 1;
    } else {
        // Clear current dino 
        drawRectangle(GROUND - dino->loc.y, dino->loc.x, DINO_STILL_WIDTH, DINO_STILL_HEIGHT, BACKGROUND_COLOR);
        
        dino->lastUpdated = 0;
        dino->loc.y += dino->vel.y;
        dino->vel.y -= dino->timeInAir;
        dino->timeInAir += 1;
        
        if (dino->loc.y < 0) {
            dino->loc.y = 0;
            dino->vel.y = 0;
        }
    }
}

