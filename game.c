#include "graphics.h"
#include "dino.h"
#include "myLib.h"
#include "colors.h"
#include "main.h"

#include <stdbool.h>

#define STEP 5
#define GROUND 75

static bool jumped = false;

void drawGame(Dino *dino, bool *selectPressed, GameState *state)
{   
    if (KEY_DOWN_NOW(BUTTON_SELECT)) {
        *selectPressed = true;
        *state = PAUSED;
    }
    if (!jumped) {
        // If on ground and up pressed, jump!
        if (KEY_DOWN_NOW(BUTTON_UP) && dino->loc.y == 0) {
            jumped = true;
            dino->vel.y = 10;
            dino->timeInAir = 1;
            dino->state = STATE_STILL;
        }
    }
    jumped = KEY_DOWN_NOW(BUTTON_UP);

    updateDino(dino);
    drawDino(dino);
}

