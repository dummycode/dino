#include "img/dino_still.h"
#include "img/dino_left.h"
#include "img/dino_right.h"
#include "graphics.h"
#include "dino.h"
#include "myLib.h"
#include "colors.h"

#define STEP 20
#define GROUND 75

void drawDino(Dino *dino)
{  
    bool jump = false;
    
    if (!jump) {
        // If on ground and up pressed, jump!
        if (KEY_DOWN_NOW(BUTTON_UP) && dino->loc.y == 0) {
            jump = true;
            dino->vel.y = 5;
            dino->timeInAir = 1;
            dino->state = STATE_STILL;
        }
    }
    jump = KEY_DOWN_NOW(BUTTON_UP);
    
    // Clear old dino
    drawRectangle(GROUND - dino->loc.y, dino->loc.x, DINO_STILL_HEIGHT, DINO_STILL_HEIGHT, BACKGROUND_COLOR);
    
    updateDino(dino);
    
    switch (dino->state) {
        case STATE_STILL:
            if (dino->loc.y == 0) {
                dino->state = STATE_RIGHT;
                drawImage(GROUND - dino->loc.y, dino->loc.x, DINO_RIGHT_HEIGHT, DINO_RIGHT_WIDTH, dino_right);
            } else {
                drawImage(GROUND - dino->loc.y, dino->loc.x, DINO_STILL_HEIGHT, DINO_STILL_WIDTH, dino_still);
            }
            break;
        case STATE_RIGHT:
            if (dino->feet.right < STEP) {
                dino->feet.right += 1;
            } else {
                dino->feet.right = 0;
                dino->state = STATE_LEFT;
                drawImage(GROUND - dino->loc.y, dino->loc.x, DINO_LEFT_HEIGHT, DINO_LEFT_WIDTH, dino_left);
            }
            break;
        case STATE_LEFT:
            if (dino->feet.left < STEP) {
                dino->feet.left += 1;
            } else {
                dino->feet.left = 0;
                dino->state = STATE_RIGHT;
                drawImage(GROUND - dino->loc.y, dino->loc.x, DINO_RIGHT_HEIGHT, DINO_RIGHT_WIDTH, dino_right);
            }
            break;
    }
}

void updateDino(Dino *dino) {
    dino->loc.y += dino->vel.y;
    dino->vel.y -= dino->timeInAir * dino->timeInAir;
    dino->timeInAir += 1;
    if (dino->loc.y < 0) {
        dino->loc.y = 0;
        dino->vel.y = 0;
    }
}

