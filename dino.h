#ifndef DINO_H
#define DINO_H

#include <stdbool.h>

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
    unsigned int left, right;
} Feet;

typedef struct {
    DinoState state;
    Point loc;
    Vector vel;
    Feet feet;
    int lastUpdated;
    int timeInAir;
} Dino;

// Prototypes
void drawDino(Dino *dino);
void updateDino(Dino *dino);

#endif

