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
#include "img/launch.h"

#include <stdbool.h>
#include <limits.h>
#include <stdio.h>

// Vars
volatile unsigned int counter;

unsigned int highScore = 0;

int main(void)
{
    REG_DISPCNT = MODE3 | BG2_ENABLE;

    counter = 0;

    GameState state = LAUNCH_DRAW;

    uint_t previousButtons = BUTTONS;
    uint_t currentButtons = BUTTONS;

    Dino dino = (Dino) {
        STATE_STILL,
        (Point) {0, 75}, // Current location
        (Point) {0, 0}, // New location
        (Vector) {0, 0}, // Current velocity
        (Vector) {0, 0}, // New velocity
        (Feet) {0, 0},
        0,
    };

    Enemy enemies[2];

    while (1) {
      currentButtons = BUTTONS;
        counter += 1;

        switch (state) {
            case LAUNCH_DRAW:
                waitForVblank();
                drawLaunch();
                state = LAUNCH;
                break;

            case LAUNCH:
              if (KEY_JUST_PRESSED(BUTTON_START, previousButtons, currentButtons)) {
                  clearScreen();
                  state = MENU_DRAW;
              }
              break;

            case MENU_DRAW:
              waitForVblank();
              drawMenu();
              state = MENU;
              break;
            case MENU:
                if (KEY_JUST_PRESSED(BUTTON_SELECT, previousButtons, currentButtons)) {
                  // Clear screen
                  drawRectangle(24, 27, 186, 106, BLACK);
                  drawRectangle(27, 30, 180, 100, TEXT_COLOR);
                  state = RULES;
                }
                else if (KEY_JUST_PRESSED(BUTTON_START, previousButtons, currentButtons)) {
                  // Reset game state
                  resetGame(enemies);

                  dino = (Dino) {
                      STATE_STILL,
                      (Point) {0, 75}, // Current location
                      (Point) {0, 0}, // New location
                      (Vector) {0, 0}, // Current velocity
                      (Vector) {0, 0}, // New velocity
                      (Feet) {0, 0},
                      0,
                  };

                  // Clear screen
                  clearScreen();
                  state = PLAYING;
                }
                break;

            case PLAYING:
                drawGame(&dino, enemies, previousButtons, currentButtons, &state);
                break;

            case PAUSED:
                drawPauseMenu();

                if (KEY_JUST_PRESSED(BUTTON_START, previousButtons, currentButtons)) {
                    // Clear screen
                    drawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BACKGROUND_COLOR);
                    state = PLAYING;
                }

                if (KEY_JUST_PRESSED(BUTTON_SELECT, previousButtons, currentButtons)) {
                    // Clear screen
                    clearScreen();
                    state = MENU_DRAW;
                }
                break;

            case LOST:
                drawLost();

                if (KEY_JUST_PRESSED(BUTTON_START, previousButtons, currentButtons)) {
                    // Clear screen
                    clearScreen();
                    state = MENU_DRAW;
                }
                break;

            case RULES:
                drawRules();

                if (KEY_JUST_PRESSED(BUTTON_START, previousButtons, currentButtons)) {
                    // Clear screen
                    clearScreen();
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
void drawMenu()
{
    waitForVblank();
    drawImage(10, 65, 110, 58, title);
    drawString(75, 60, "Press start to begin", TEXT_COLOR, BACKGROUND_COLOR);
    drawString(85, 42, "Press select to read rules", TEXT_COLOR, BACKGROUND_COLOR);
    char buffer[1024];
    sprintf(buffer, "High score: %05u", highScore);
    drawString(95, 68, buffer, TEXT_COLOR, BACKGROUND_COLOR);
}

/**
 * Logic to draw the pause menu
 */
void drawPauseMenu()
{
    waitForVblank();
    drawString(13, 5, "Paused. Press start to continue.", TEXT_COLOR, BACKGROUND_COLOR);
}

/**
 * Logic to draw the rules
 */
void drawRules()
{
    waitForVblank();
    drawString(29, 32, "Rules", WHITE, TEXT_COLOR);
    drawString(41, 32, "Press \"Up\" to jump", WHITE, TEXT_COLOR);
    drawString(51, 32, "Avoid the enemies", WHITE, TEXT_COLOR);
    drawString(61, 32, "Have fun", WHITE, TEXT_COLOR);
    drawString(71, 32, "That's it :)", WHITE, TEXT_COLOR);
    drawString(117, 32, "Start to close", WHITE, TEXT_COLOR);
}

/**
 * Logic to draw the lost page
 */
void drawLost()
{
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
void clearScreen()
{
    drawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BACKGROUND_COLOR);
}

/**
 * Logic to draw the launch screen
 */
void drawLaunch()
{
    drawImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, launch);
}
