#ifndef ENEMY_H
#define ENEMY_H

#include "dino.h"

#include <stdbool.h>

typedef struct {
    unsigned int width, height;
} Size;

typedef struct {
    bool alive;
    Point p;
    Point np;
    Vector v;
    Vector nv;
    Size size;
    const unsigned short* image;
} Enemy;

// Prototypes
void drawEnemy(Enemy *enemy);
void updateEnemy(Enemy *enemy);
void clearOldEnemy(Enemy *enemy);

extern volatile unsigned short *pcounter;
extern volatile int num_enemies;

#endif

