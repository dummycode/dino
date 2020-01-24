#ifndef MAIN_H
#define MAIN_H

#include "types.h"
#include "draw.h"

typedef enum {
    MENU_DRAW,
    MENU,
    APP_INIT,
    PLAYING,
    DRAW_PAUSED,
    PAUSED,
    DRAW_RULES,
    RULES,
    LOST,
} GameState;

void drawMenu();
void drawPauseMenu();
void drawRules();
void drawLost();
void clearScreen();
void drawLaunch();

extern volatile int num_enemies;
extern volatile unsigned int score;

#endif
