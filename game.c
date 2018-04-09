#include "graphics.h"
#include "dino.h"
#include "myLib.h"
#include "colors.h"
#include "main.h"
#include "text.h"
#include "game.h"
#include "enemy.h"
#include "img/bird.h"

#include <stdio.h>
#include <stdbool.h>

#define GROUND 100
#define MAX_ENEMIES 2
#define UNUSED(x) (void) x

bool jumped = false;
int step = 50;
const int minStep = 2;
volatile unsigned int score;
volatile int num_enemies = 0;

void drawGame(Dino *dino, Enemy enemies[], bool *selectPressed, GameState *state)
{   
    if (KEY_DOWN_NOW(BUTTON_SELECT)) {
        *selectPressed = true;
        *state = PAUSED;
    }
    if (!jumped) {
        // If on ground and up pressed, jump!
        if (KEY_DOWN_NOW(BUTTON_UP) && (dino->p.y == GROUND - DINO_HEIGHT)) {
            jumped = true;
            dino->v.y = -4;
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
    
        
    if (didLose(dino, enemies)) {
        // TODO: Update high score
        clearScreen();
        // Clear screen
        drawRectangle(24, 27, 186, 106, BLACK);
        drawRectangle(27, 30, 180, 100, TEXT_COLOR);
        *state = LOST;
    }
        
    if (num_enemies == 0) {
        enemies[0] = (Enemy) {
            true,
            (Point) {240, 65},
            (Point) {0, 0},
            (Vector) {-4, 0},
            (Vector) {0, 0},
            (Size) {15, 15},
            bird,
        };
        num_enemies += 1;
    }
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
    DMA[3].dst = &videoBuffer[(OFFSET(GROUND, 0, SCREEN_WIDTH))];
    DMA[3].cnt = SCREEN_WIDTH | DMA_SOURCE_FIXED | DMA_ON;
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


/**
 * Checks to see if player has lost the game by checking
 * to see if the dino is in contact with any enemy
 */
bool didLose(Dino *dino, Enemy *enemies)
{
    UNUSED(dino);
    // Iterate through all enemies, calculating if the dino is colliding with any of them
    for (int i = 0; i < MAX_ENEMIES; i++) {
        Enemy enemy = enemies[i];
        if (enemy.alive) {
            // If left corner is in
            int x = dino->p.x;
            int y = dino->p.y;
            if (x > enemy.p.x && (x < enemy.p.x + (int) enemy.size.width) && y > enemy.p.y && (y < enemy.p.y + (int) enemy.size.height)) {
                return true;
            }
            // Bottom left
            x = dino->p.x;
            y = dino->p.y + DINO_HEIGHT;
            if (x > enemy.p.x && (x < enemy.p.x + (int) enemy.size.width) && y > enemy.p.y && (y < enemy.p.y + (int) enemy.size.height)) {
                return true;
            }
            // Bottom right
            x = dino->p.x + DINO_WIDTH;
            y = dino->p.y + DINO_HEIGHT;
            if (x > enemy.p.x && (x < enemy.p.x + (int) enemy.size.width) && y > enemy.p.y && (y < enemy.p.y + (int) enemy.size.height)) {
                return true;
            }
            // Top right
            x = dino->p.x + DINO_WIDTH;
            y = dino->p.y;
            if (x > enemy.p.x && (x < enemy.p.x + (int) enemy.size.width) && y > enemy.p.y && (y < enemy.p.y + (int) enemy.size.height)) {
                return true;
            }
        }
    }
    return false;
}

/**
 * Reset the game to new
 */
void resetGame()
{
    jumped = false;
    step = 100;
    score = 0;
}

