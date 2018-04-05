#include "myLib.h"
#include "dino.h"
#include "img/title.h"
#include "graphics.h"
#include "colors.h"
#include "text.h"
#include "main.h"
#include "game.h"

#include <stdbool.h>

int main(void) 
{
    REG_DISPCNT = MODE3 | BG2_ENABLE;
    
    drawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BACKGROUND_COLOR);
    
    GameState state = MENU;
    
    bool selectPressed = false;
    bool startPressed = false;
    
    Dino dino = (Dino) {
        STATE_STILL,
        (Point) {0, 0},
        (Vector) {0, 0},
        (Feet) {0, 0},
        0,
        0,
    };

    while (1) {
        waitForVblank();
        switch (state) {
            case MENU:
                drawMenu();
                
                if (!startPressed) {
                    if (KEY_DOWN_NOW(BUTTON_START)) {
                        // Clear screen
                        clearScreen();
                        state = PLAYING;
                    }
                }
                startPressed = KEY_DOWN_NOW(BUTTON_START);
                
                if (!selectPressed) {
                    if (KEY_DOWN_NOW(BUTTON_SELECT)) {
                        selectPressed = true;
                        // Clear screen
                        state = RULES;
                    }   
                }
                selectPressed = KEY_DOWN_NOW(BUTTON_SELECT);
                break;
                
            case PLAYING:
                drawGame(&dino, &selectPressed, &state);
                break;
                
            case PAUSED:
                drawPauseMenu();
                
                if (KEY_DOWN_NOW(BUTTON_START)) {
                    // Clear screen
                    drawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BACKGROUND_COLOR);
                    state = PLAYING;
                }
                
                if (!selectPressed) {
                    if (KEY_DOWN_NOW(BUTTON_SELECT)) {
                        selectPressed = true;
                        // Clear screen
                        clearScreen();
                        state = MENU;
                    }   
                }
                selectPressed = KEY_DOWN_NOW(BUTTON_SELECT);
                break;
                
            case RULES:
                drawRules();
                
                if (!startPressed) {
                    if (KEY_DOWN_NOW(BUTTON_START)) {
                        startPressed = true;
                        // Clear screen
                        clearScreen();
                        state = MENU;
                    }   
                }
                selectPressed = KEY_DOWN_NOW(BUTTON_START); 
                break;  
        }
    }
    return 0;
}

/**
 * Logic to draw the main menu
 */
void drawMenu() 
{
    drawString(10, 10, "Press start to begin", TEXT_COLOR, BACKGROUND_COLOR);
    drawString(20, 10, "Press select to read rules", TEXT_COLOR, BACKGROUND_COLOR);
    drawImage(10, 65, 110, 58, title);
}

/**
 * Logic to draw the pause menu
 */
void drawPauseMenu()
{
    drawString(10, 10, "Paused. Press start to continue.", TEXT_COLOR, BACKGROUND_COLOR);
}

/**
 * Logic to draw the rules
 */
void drawRules()
{
    drawString(10, 10, "Rules", TEXT_COLOR, BACKGROUND_COLOR);
}

/**
 * Clears the screen to background color
 */
void clearScreen()
{
    drawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BACKGROUND_COLOR);
}
