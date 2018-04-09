#ifndef MAIN_H
#define MAIN_H

typedef enum {
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

extern volatile int num_enemies;
extern volatile unsigned int score;

#endif

