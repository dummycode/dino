#ifndef MAIN_H
#define MAIN_H

typedef enum {
    LAUNCH,
    MENU,
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

#endif

