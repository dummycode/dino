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
int score = 0;
int step = 10;
int minStep = 2;

void drawGame(Dino *dino, bool *selectPressed, GameState *state)
{   
    if (KEY_DOWN_NOW(BUTTON_SELECT)) {
        *selectPressed = true;
        *state = PAUSED;
    }
    if (!jumped) {
        // If on ground and up pressed, jump!
        if (KEY_DOWN_NOW(BUTTON_UP) && dino->p.y == 0) {
            jumped = true;
            dino->v.y = 8;
            dino->timeInAir = 0;
            dino->state = STATE_STILL;
        }
    }
    jumped = KEY_DOWN_NOW(BUTTON_UP);

    updateDino(dino);
    updateDinoState(dino);
    
    waitForVblank();
    drawGround();
    clearOldDino(dino);
    
    // Update values of dino
    dino->p = dino->np;
    dino->v = dino->nv;
    drawDino(dino);
    
    if (*pcounter % step == 0) {
        score += 1;
    }
    drawScore(&score);
}

void drawScore(int *score)
{
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

void drawGround()
{
    short source = BACKGROUND_COLOR;
    DMA[3].src = &source;
    DMA[3].dst = &videoBuffer[(OFFSET(GROUND + DINO_HEIGHT, 0, SCREEN_WIDTH))];
    DMA[3].cnt = SCREEN_WIDTH | DMA_SOURCE_FIXED | DMA_ON;
}

