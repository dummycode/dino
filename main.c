#include <stdbool.h>
#include <limits.h>
#include <stdio.h>

#include "myLib.h"
#include "dino.h"
#include "img/title.h"
#include "graphics.h"
#include "colors.h"
#include "text.h"
#include "main.h"
#include "game.h"
#include "enemy.h"
#include "img/bird.h"
#include "draw.h"

// Vars
volatile unsigned int counter;
unsigned int highScore = 0;

/*
 * Main method
 */
int main(void) {
    REG_DISPCNT = MODE3 | BG2_ENABLE;

    counter = 0;

    GameState state = MENU_DRAW;
    AppState appState = initialAppState();

    uint_t previousButtons = BUTTONS;
    uint_t currentButtons = BUTTONS;

    while (true) {
        currentButtons = BUTTONS;
        counter += 1;
        appState.tick += 1;

        switch (state) {
            case MENU_DRAW:
                waitForVblank();
                drawMenu();
                state = MENU;
                break;

            case MENU:
                if (KEY_JUST_PRESSED(BUTTON_SELECT, previousButtons, currentButtons)) {
                    state = DRAW_RULES;
                }
                else if (KEY_JUST_PRESSED(BUTTON_START, previousButtons, currentButtons)) {
                    // Reset game state
                    resetAppState(&appState);

                    // Clear screen
                    clearScreen();

                    state = PLAYING;
                }
                break;

            case PLAYING:
                updateAppState(&appState, previousButtons, currentButtons);
                drawAppState(&appState);

                if (KEY_JUST_PRESSED(BUTTON_SELECT, previousButtons, currentButtons)) {
                    state = DRAW_PAUSED;
                }

                break;

            case DRAW_PAUSED:
                drawPauseMenu();
                state = PAUSED;
                break;

            case PAUSED:
                if (KEY_JUST_PRESSED(BUTTON_START, previousButtons, currentButtons)) {
                    // Clear screen
                    drawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BACKGROUND_COLOR);
                    state = PLAYING;
                }

                if (KEY_JUST_PRESSED(BUTTON_SELECT, previousButtons, currentButtons)) {
                    // Clear screen
                    state = MENU_DRAW;
                }
                break;

            case LOST:
                drawLost();

                if (KEY_JUST_PRESSED(BUTTON_START, previousButtons, currentButtons)) {
                    // Clear screen
                    state = MENU_DRAW;
                }
                break;

            case DRAW_RULES:
                drawRules();
                state = RULES;
                break;

            case RULES:
                if (KEY_JUST_PRESSED(BUTTON_START, previousButtons, currentButtons)) {
                    state = MENU_DRAW;
                }
                break;

            default:
                break;
        }
        previousButtons = currentButtons;
    }
    return 0;
}

/**
 * Logic to draw the main menu
 */
void drawMenu() {
    waitForVblank();
    drawFullScreenRectangle(BACKGROUND_COLOR);
    drawImage(10, 65, 110, 58, title);
    drawString(75, 60, "Press start to begin", TEXT_COLOR, BACKGROUND_COLOR);
    drawString(85, 42, "Press select to read rules", TEXT_COLOR, BACKGROUND_COLOR);
    char buffer[1024];
    sprintf(buffer, "High score: %05u", highScore);
    drawString(105, 68, buffer, TEXT_COLOR, BACKGROUND_COLOR);
}

/**
 * Logic to draw the pause menu
 */
void drawPauseMenu() {
    drawRectangle(24, 27, 186, 106, BLACK);
    drawRectangle(27, 30, 180, 100, TEXT_COLOR);
    drawString(29, 32, "Paused", WHITE, TEXT_COLOR);
    drawString(46, 32, "Press start to continue", WHITE, TEXT_COLOR);
    drawString(56, 32, "Select to quit", WHITE, TEXT_COLOR);
}

/**
 * Logic to draw the rules
 */
void drawRules() {
    waitForVblank();
    drawRectangle(24, 27, 186, 106, BLACK);
    drawRectangle(27, 30, 180, 100, TEXT_COLOR);
    drawString(29, 32, "Rules", WHITE, TEXT_COLOR);
    drawString(46, 32, "Press \"Up\" to jump", WHITE, TEXT_COLOR);
    drawString(56, 32, "Avoid the enemies", WHITE, TEXT_COLOR);
    drawString(66, 32, "Have fun", WHITE, TEXT_COLOR);
    drawString(76, 32, "That's it :)", WHITE, TEXT_COLOR);
    drawString(117, 32, "Start to close", WHITE, TEXT_COLOR);
}

/**
 * Logic to draw the lost page
 */
void drawLost() {
    waitForVblank();
    drawString(29, 32, "You lost :(", WHITE, TEXT_COLOR);
    char buffer[1024];
    sprintf(buffer, "Your score: %u", score);
    drawString(41, 32, buffer, WHITE, TEXT_COLOR);
    drawString(117, 32, "Start to close", WHITE, TEXT_COLOR);
}

/**
 * Clears the screen to background color
 */
void clearScreen() {
    drawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BACKGROUND_COLOR);
}

