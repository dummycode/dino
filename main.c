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
    
    drawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BACKGROUND_COLOR);
    
    GameState state = LAUNCH;
    
    bool selectPressed = false;
    bool startPressed = false;
    
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
        counter += 1;
        
        char buffer[1024];
        drawString(0, 0, buffer, TEXT_COLOR, BACKGROUND_COLOR);
      
        switch (state) {
            case LAUNCH:
                drawLaunch();
                
                if (!startPressed) {
                    if (KEY_DOWN_NOW(BUTTON_START)) {
                        startPressed = true;
                        // Clear screen
                        clearScreen();
                        state = MENU;
                    }   
                }
                startPressed = KEY_DOWN_NOW(BUTTON_START); 
                break;  
                
            case MENU:
                drawMenu();
                
                if (!startPressed) {
                    if (KEY_DOWN_NOW(BUTTON_START)) {
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
                }
                startPressed = KEY_DOWN_NOW(BUTTON_START);
                
                if (!selectPressed) {
                    if (KEY_DOWN_NOW(BUTTON_SELECT)) {
                        selectPressed = true;
                        // Clear screen
                        drawRectangle(24, 27, 186, 106, BLACK);
                        drawRectangle(27, 30, 180, 100, TEXT_COLOR);
                        state = RULES;
                    }   
                }
                selectPressed = KEY_DOWN_NOW(BUTTON_SELECT);
                break;
                
            case PLAYING:
                drawGame(&dino, enemies, &selectPressed, &state);
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
                
            case LOST:
                drawLost();
                
                if (!startPressed) {
                    if (KEY_DOWN_NOW(BUTTON_START)) {
                        startPressed = true;
                        // Clear screen
                        clearScreen();
                        state = MENU;
                    }   
                }
                startPressed = KEY_DOWN_NOW(BUTTON_START); 
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
                startPressed = KEY_DOWN_NOW(BUTTON_START); 
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
    waitForVblank();
    drawImage(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, launch);
}
