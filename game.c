#include "graphics.h"
#include "dino.h"
#include "myLib.h"
#include "colors.h"
#include "main.h"
#include "text.h"
#include "game.h"
#include "enemy.h"

#include <stdio.h>
#include <stdbool.h>

#define GROUND 75
#define MAX_ENEMIES 2
#define UNUSED(x) (void) x

bool jumped = false;
int step = 50;
const int minStep = 2;
volatile unsigned int score;

void drawGame(Dino *dino, Enemy enemies[], bool *selectPressed, GameState *state)
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
    
    updateEnemies(enemies);
    
    waitForVblank();
    
    drawGround();
    clearOldDino(dino);
    clearOldEnemies(enemies);
    
    // Update values of enemies
    updateLocationOfEnemies(enemies);
    drawEnemies(enemies);
    
    
    // Update values of dino
    dino->p = dino->np;
    dino->v = dino->nv;
    drawDino(dino);
    drawScore();
}

void drawScore()
{
    if (*pcounter % step == 0) {
        score += 1;
    }
    
    if (score % 50 == 0) {
        step -= 5;
        if (step < minStep) {
            step = minStep;
        }
    }
    
    char buffer[1024];
    sprintf(buffer, "Score: %d", score);
    drawString(4, 170, buffer, TEXT_COLOR, BACKGROUND_COLOR);
}

void drawGround()
{
    short source = BACKGROUND_COLOR;
    DMA[3].src = &source;
    DMA[3].dst = &videoBuffer[(OFFSET(GROUND + DINO_HEIGHT, 0, SCREEN_WIDTH))];
    DMA[3].cnt = SCREEN_WIDTH | DMA_SOURCE_FIXED | DMA_ON;
}

void resetGame()
{
    jumped = false;
    step = 100;
    score = 0;
}

void updateLocationOfEnemies(Enemy *enemies)
{
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].alive)
            enemies[i].p.x = enemies[i].np.x;
            enemies[i].p.y = enemies[i].np.y;
    }
}

void updateEnemies(Enemy *enemies)
{
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].alive)
            updateEnemy(&enemies[i]);
    }
}

void drawEnemies(Enemy *enemies)
{
    for (int i = 0; i < MAX_ENEMIES; i++) {
        if (enemies[i].alive) {
            drawEnemy(&enemies[i]);
        }
    }
}

void clearOldEnemies(Enemy *enemies)
{
    for (int i = 0; i < MAX_ENEMIES; i++) {
        clearOldEnemy(&enemies[i]);
    }
}

bool didLose(Dino *dino)
{
    UNUSED(dino);
    return true;
}
