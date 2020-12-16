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

void enemy__update(Enemy *enemy);
void enemy__clear_old(Enemy *enemy);
void enemy__draw(Enemy *enemy);
void enemy__next(Enemy *enemy);
Enemy enemy__random();

extern volatile unsigned short *pcounter;
extern volatile int num_enemies;

#endif
