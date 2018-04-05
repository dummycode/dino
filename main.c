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
        0, 
        false, 
        0
    };
    
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
                drawDino(&dino);
                break;
            case PAUSED:
                break;
        }
    }
    return 0;
}

void drawMenu() 
{
    drawString(0, 0, "Press start to begin", 0x294a, BACKGROUND_COLOR);
}
