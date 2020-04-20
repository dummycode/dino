#ifndef DINO_H
#define DINO_H

#include <stdbool.h>
#include "types.h"

typedef enum {
    STATE_STILL,
    STATE_RIGHT,
    STATE_LEFT,
} DinoState;

typedef struct {
    int x, y;
} Point;

typedef struct {
    int x, y;
} Vector;

typedef struct {
    DinoState state;
    Point p;
    Point np;
    Vector v;
    Vector nv;
    int timeInAir;
} Dino;

// Prototypes
void dino__update_state(Dino *dino);
void dino__jump(Dino *dino);
void dino__update(Dino *dino);
void dino__clear_old(Dino *dino);
void dino__draw(Dino *dino);
void dino__next(Dino *dino);

extern volatile unsigned short *pcounter;

#endif
