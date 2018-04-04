#include "img/dino_still.h"
#include "img/dino_left.h"
#include "img/dino_right.h"
#include "graphics.h"
#include "colors.h"
#include "dino.h"
#include "myLib.h"

#define STEP 20
#define GROUND 75

enum DinoState {
	STATE_STILL,
    STATE_RIGHT,
    STATE_LEFT,
};

void running(Dino *dino)
{
    enum DinoState state = STATE_STILL;
    
    drawRectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, BACKGROUND_COLOR);
    
    int left = 0, right = 0;
    
    bool jump = false;
    
    while (1) {
        waitForVblank();
        if (!jump && KEY_DOWN_NOW(BUTTON_INDEX_UP)) {
            dino->loc.y = 50;
        }
        switch (state) {
            case STATE_STILL:
                state = STATE_RIGHT;
                drawImage(GROUND + dino->loc.y, dino->loc.x, DINO_RIGHT_HEIGHT, DINO_RIGHT_WIDTH, dino_right);
                break;
            case STATE_RIGHT:
                if (right < STEP) {
                    right += 1;
                } else {
                    right = 0;
                    state = STATE_LEFT;
                    drawImage(GROUND + dino->loc.y, dino->loc.x, DINO_LEFT_HEIGHT, DINO_LEFT_WIDTH, dino_left);
                }
                break;
            case STATE_LEFT:
                if (left < STEP) {
                    left += 1;
                } else {
                    left = 0;
                    state = STATE_RIGHT;
                    drawImage(GROUND + dino->loc.y, dino->loc.x, DINO_RIGHT_HEIGHT, DINO_RIGHT_WIDTH, dino_right);
                }
                break;
        }
    }
}

