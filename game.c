#include "graphics.h"
#include "dino.h"
#include "myLib.h"
#include "colors.h"
#include "main.h"
#include "text.h"
#include "game.h"
#include "enemy.h"
#include "img/bird.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define GROUND 100
#define MAX_ENEMIES 4
#define MIN_Y 50
#define SCORE_DIVIDER 100

bool jumped = false;
int mult = 1;
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
        // Update high score
        score = score / SCORE_DIVIDER;
        extern unsigned int highScore;
        if (score > highScore) {
            highScore = score;
        }
        clearScreen();

        // Draw dialog box
        drawRectangle(24, 27, 186, 106, BLACK);
        drawRectangle(27, 30, 180, 100, TEXT_COLOR);
        *state = LOST;
    }

    if (num_enemies < MAX_ENEMIES) {
        // Decide if we should place another enemy
        int p = rand() % (1000 + 1 - 0) + 0;
        if (p < 10) {
            int yStart = rand() % (65 + 1 - MIN_Y) + MIN_Y;
            int xVelocity = rand() % (-3 + 1 - (-3)) + (-3);
            int yVelocity = rand() % (2 + 1 - (-2)) + (-2);
            int i;
            for (i = 0; i < MAX_ENEMIES; i++) {
                if (!enemies[i].alive)
                    break;
            }
            enemies[i] = (Enemy) {
                true,
                (Point) {225, yStart},
                (Point) {0, 0},
                (Vector) {xVelocity, yVelocity},
                (Vector) {0, 0},
                (Size) {15, 15},
                bird,
            };
            num_enemies += 1;
        }
    }
}

void drawScore()
{
    score += 1 * mult;

    if (score % 25 == 0) {
        mult += 1;
    }

    char buffer[1024];
    sprintf(buffer, "Score: %d", score / SCORE_DIVIDER);
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
    for (int i = 0; i < MAX_ENEMIES; i++) {
        Enemy enemy = enemies[i];
        if (enemy.alive) {
            // If left corner is in
            int x = enemy.p.x;
            int y = enemy.p.y;
            if (x > dino->p.x && (x < (dino->p.x + DINO_WIDTH)) && y > dino->p.y && (y < (dino->p.y + DINO_HEIGHT))) {
                return true;
            }
            // Bottom left
            x = enemy.p.x;
            y = enemy.p.y + enemy.size.height;
            if (x > dino->p.x && (x < (dino->p.x + DINO_WIDTH)) && y > dino->p.y && (y < (dino->p.y + DINO_HEIGHT))) {
                return true;
            }
            // Bottom right
            x = enemy.p.x + enemy.size.width;
            y = enemy.p.y + enemy.size.height;
            if (x > dino->p.x && (x < (dino->p.x + DINO_WIDTH)) && y > dino->p.y && (y < (dino->p.y + DINO_HEIGHT))) {
                return true;
            }
            // Top right
            x = enemy.p.x + enemy.size.width;
            y = enemy.p.y;
            if (x > dino->p.x && (x < (dino->p.x + DINO_WIDTH)) && y > dino->p.y && (y < (dino->p.y + DINO_HEIGHT))) {
                return true;
            }
        }
    }
    return false;
}

/**
 * Reset the game to new
 */
void resetGame(Enemy enemies[])
{
    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i].alive = false;
    }
    num_enemies = 0;
    jumped = false;
    mult = 0;
    score = 0;
}
