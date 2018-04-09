#include "graphics.h"
#include "enemy.h"
#include "myLib.h"
#include "colors.h"

#include <stdbool.h>

#define GROUND 100
#define MIN_Y 40

void drawEnemy(Enemy *enemy) 
{
    drawImage(enemy->p.y, enemy->p.x, enemy->size.height, enemy->size.width, enemy->image);
}

void updateEnemy(Enemy *enemy) 
{
    if (enemy->p.y + enemy->size.height > GROUND || enemy->p.y < MIN_Y) {
        enemy->v.y = -enemy->v.y;
    }

    enemy->np.x = enemy->p.x + enemy->v.x;
    enemy->np.y = enemy->p.y + enemy->v.y;
    
    if (enemy->np.x < 0) {
        enemy->alive = false;
        num_enemies -= 1;
    } 
    
    enemy->nv.x = enemy->v.x;
    enemy->nv.y = enemy->v.y;
}

void clearOldEnemy(Enemy *enemy)
{
    drawRectangle(enemy->p.y, enemy->p.x, enemy->size.height, enemy->size.width, BACKGROUND_COLOR);
}

