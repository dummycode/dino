#include "graphics.h"
#include "enemy.h"
#include "myLib.h"
#include "colors.h"

#include <stdbool.h>

#define GROUND 75
#define MIN_HEIGHT 0

void drawEnemy(Enemy *enemy) 
{
//    if (enemy->p.y < 0 || enemy->p.x < 0 || enemy->p.y + enemy->size.width > SCREEN_WIDTH - 1 || enemy->p.x + enemy->size.height > SCREEN_HEIGHT - 1) {
//        drawImageSketchy(enemy->p.y, enemy->p.x, enemy->size.height, enemy->size.width, enemy->image);
//    }
    drawImage(enemy->p.y, enemy->p.x, enemy->size.height, enemy->size.width, enemy->image);
}

void updateEnemy(Enemy *enemy) 
{
    enemy->np.x = enemy->p.x + enemy->v.x;
    enemy->np.y = enemy->p.y + enemy->v.y;
    
    if (enemy->np.x < 0) {
        enemy->alive = false;
    } 
    
    if (enemy->np.y + enemy->size.height > GROUND || enemy->np.y < MIN_HEIGHT) {
        enemy->np.y = GROUND + MIN_HEIGHT / 2;
    }
    
    enemy->nv.x = enemy->v.x;
    enemy->nv.y = enemy->v.y;
}

void clearOldEnemy(Enemy *enemy)
{
    drawRectangle(enemy->p.y, enemy->p.x, enemy->size.height, enemy->size.width, BACKGROUND_COLOR);
}

