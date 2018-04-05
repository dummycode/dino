#include "myLib.h"
#include "dino.h"
#include "graphics.h"
#include "colors.h"
#include "text.h"
#include "main.h"

#include <stdbool.h>

typedef enum {
    MENU,
    PLAYING,
    PAUSED,
} GameState;

int main(void) 
{
    REG_DISPCNT = MODE3 | BG2_ENABLE;
    
    drawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BACKGROUND_COLOR);
        
    Dino dino = (Dino) {
        STATE_STILL,
        (Point) {0, 0}, 
        (Vector) {0, 0}, 
        (Feet) {0, 0},
        0, // Last updated
        0, 
        false, 
        0
    };
    
    bool jumped = false;
    
    GameState state = MENU;
    
    while (1) {
        waitForVblank();
        switch (state) {
            case MENU:
                drawMenu();
                if (KEY_DOWN_NOW(BUTTON_START)) {
                    // Clear screen
                    drawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BACKGROUND_COLOR);
                    state = PLAYING;
                }
                break;
            case PLAYING:
                if (KEY_DOWN_NOW(BUTTON_SELECT)) {
                    state = PAUSED;
                }
                if (!jumped) {
                    // If on ground and up pressed, jump!
                    if (KEY_DOWN_NOW(BUTTON_UP) && dino.loc.y == 0) {
                        jumped = true;
                        dino.vel.y = 10;
                        dino.timeInAir = 1;
                        dino.state = STATE_STILL;
                    }
                }
                jumped = KEY_DOWN_NOW(BUTTON_UP);
    
                updateDino(&dino);
                drawDino(&dino);
                break;
            case PAUSED:
                drawPauseMenu();
                if (KEY_DOWN_NOW(BUTTON_START)) {
                    // Clear screen
                    drawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BACKGROUND_COLOR);
                    state = PLAYING;
                }
                break;
        }
    }
    return 0;
}

void drawMenu() 
{
    drawString(10, 10, "Press start to begin", TEXT_COLOR, BACKGROUND_COLOR);
}

void drawPauseMenu()
{
    drawString(10, 10, "Paused. Press start to continue.", TEXT_COLOR, BACKGROUND_COLOR);
}
