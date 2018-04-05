#ifndef MAIN_H
#define MAIN_H

typedef enum {
    MENU,
    PLAYING,
    PAUSED,
    RULES,
} GameState;

void drawMenu();
void drawPauseMenu();
void drawRules();
void clearScreen();

#endif

