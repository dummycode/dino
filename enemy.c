#include "graphics.h"
#include "enemy.h"
#include "myLib.h"
#include "colors.h"
#include "img/bird.h"

#include <stdbool.h>
#include <stdlib.h>

#define GROUND 100
#define MIN_Y 50

void enemy__update(Enemy *enemy) {
    // Flip direction of enemy if hits ground or "top"
    if (enemy->p.y + enemy->size.height > GROUND || enemy->p.y < MIN_Y) {
        enemy->nv.y = -enemy->v.y;
    }

    enemy->np.x = enemy->p.x + enemy->nv.x;
    enemy->np.y = enemy->p.y + enemy->nv.y;

    if (enemy->np.x < 0) {
        enemy->alive = false;
        num_enemies -= 1;
    }
}

void enemy__clear_old(Enemy *enemy) {
    drawRectangle(enemy->p.y, enemy->p.x, enemy->size.height, enemy->size.width, BACKGROUND_COLOR);
}

void enemy__draw(Enemy *enemy) {
    drawImage(enemy->np.y, enemy->np.x, enemy->size.height, enemy->size.width, enemy->image);

    // TODO: this may go elsewhere
    enemy__next(enemy);
}

void enemy__next(Enemy *enemy) {
    enemy->p = enemy->np;
    enemy->v = enemy->nv;
}

/*
 * Returns an enemy in a random location
 */
Enemy enemy__random() {
    int yStart = rand() % (65 + 1 - MIN_Y) + MIN_Y;
    int xVelocity = rand() % (-3 + 1 - (-3)) + (-3);
    int yVelocity = rand() % (2 + 1 - (-2)) + (-2);
    Enemy enemy = (Enemy) {
        true,
        (Point) {225, yStart},
        (Point) {0, 0},
        (Vector) {xVelocity, yVelocity},
        (Vector) {0, 0},
        (Size) {15, 15},
        bird,
    };

    return enemy;
}
