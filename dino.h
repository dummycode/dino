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
  unsigned int left, right;
} Feet;

typedef struct {
  DinoState state;
  Point p;
  Point np;
  Vector v;
  Vector nv;
  Feet feet;
  int timeInAir;
} Dino;

// Prototypes
void updateDinoState(Dino *dino);
void updateDino(Dino *dino);
void clearOldDino(Dino *dino);

extern volatile unsigned short *pcounter;

#endif
