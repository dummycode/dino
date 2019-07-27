#ifndef MAIN_H
#define MAIN_H

typedef enum {
    LAUNCH,
    LAUNCH_DRAW,
    MENU_DRAW,
    MENU,
    APP_INIT,
    PLAYING,
    PAUSED,
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

typedef unsigned int uint_t;

#endif
