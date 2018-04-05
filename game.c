#include "graphics.h"
#include "dino.h"
#include "myLib.h"
#include "colors.h"
#include "main.h"
#include "text.h"
#include "game.h"

#include <stdio.h>
#include <stdbool.h>

#define STEP 5
#define GROUND 75

bool jumped = false;
int lastUpdated = 13;
int score = 0;
int step = 12;
int minStep = 2;

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
            dino->vel.y = 15;
            dino->timeInAir = 1;
            dino->state = STATE_STILL;
        }
    }
    jumped = KEY_DOWN_NOW(BUTTON_UP);

    updateDino(dino);
    drawDino(dino);
    if (lastUpdated > step) {
        lastUpdated = 0;
        drawScore(&score);
    }
    lastUpdated++;
}

void drawScore(int *score)
{
    *score += 1;
    if (*score % 50 == 0) {
        step -= 1;
        if (step < minStep) {
            step = minStep;
        }
    }
    char buffer[1024];
    sprintf(buffer, "Score: %d", *score);
    drawString(4, 170, buffer, TEXT_COLOR, BACKGROUND_COLOR);
}

