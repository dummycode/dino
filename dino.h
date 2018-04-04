#ifndef DINO_H
#define DINO_H

#include <stdbool.h>

typedef struct {
    unsigned int x, y;
} Point;

typedef struct {
    Point loc;
    int height; 
    bool ground;
} Dino;

// Prototypes
void running(Dino *dino);

#endif

