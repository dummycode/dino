#include "graphics.h"
#include "dino.h"
#include "myLib.h"
#include "colors.h"
#include "main.h"
#include "text.h"
#include "game.h"
#include "enemy.h"
#include "main.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define GROUND 100
#define MIN_Y 50
#define SCORE_DIVIDER 100

#define UNUSED(var) ((void) (var))

bool jumped = false;
int mult = 1;
volatile unsigned int score;
volatile int num_enemies = 0;

AppState initialAppState() {
    AppState appState;

    Dino dino = (Dino) {
        STATE_LEFT,
        (Point) {0, 75}, // Current location
        (Point) {0, 0},  // New location
        (Vector) {0, 0}, // Current velocity
        (Vector) {0, 0}, // New velocity
        0,
    };
    appState.dino = dino;

    for (unsigned int i = 0; i < MAX_ENEMIES; i++) {
        appState.enemies[i] = (Enemy) {
            .alive = false,
            (Point) {0, 0},
            (Point) {0, 0},
            (Vector) {0, 0},
            (Vector) {0, 0},
            (Size) {0, 0},
            NULL,
        };
    }

    appState.score = 0;
    appState.tick = 0;

    return appState;
}

/*
 * Reset app state at beginning of game
 */
void resetAppState(AppState *appState) {
    Dino dino = (Dino) {
        STATE_LEFT,
        (Point) {0, 75}, // Current location
        (Point) {0, 0}, // New location
        (Vector) {0, 0}, // Current velocity
        (Vector) {0, 0}, // New velocity
        0,
    };
    appState->dino = dino;

    for (unsigned int i = 0; i < MAX_ENEMIES; i++) {
        appState->enemies[i] = (Enemy) {
            .alive = false,
            (Point) {0, 0},
            (Point) {0, 0},
            (Vector) {0, 0},
            (Vector) {0, 0},
            (Size) {0, 0},
            NULL,
        };
    }

    appState->score = 0;
}

/**
 * Update the app state
 */
void updateAppState(AppState *appState, uint_t previousButtons, uint_t currentButtons) {
    // Update score every 16th tick
    if ((appState->tick & 127) == 0) {
        // TODO In the future the score should scale with speed
        appState->score += 1;
    }

    // Update feet every 8th tick
    if ((appState->tick & 63) == 0) {
        dino__update_state(&appState->dino);
    }

    if (KEY_JUST_PRESSED(BUTTON_UP, previousButtons, currentButtons)) {
        appState->dino.state = STATE_STILL;

        dino__jump(&appState->dino);
    }

    if (didLose(&appState->dino, appState->enemies)) {
        appState->dino.state = STATE_STILL;
    }

    if (num_enemies < MAX_ENEMIES) {
        // Decide if we should place another enemy
        int p = rand() % (1000 + 1 - 0) + 0;
        if (p < 10) {
            Enemy new_enemy = enemy__random();

            for (unsigned int i = 0; i < MAX_ENEMIES; i++) {
                if (!appState->enemies[i].alive) {
                    appState->enemies[i] = new_enemy;
                }
            }
        }
    }

    dino__update(&appState->dino);
}

/*
 * Checks if player is contacting an enemy
 */
bool didLose(Dino *dino, Enemy *enemies) {
    for (int i = 0; i < MAX_ENEMIES; i++) {
        Enemy enemy = enemies[i];
        if (enemy.alive) {
            // If left corner is in
            int x = enemy.p.x;
            int y = enemy.p.y;
            if (x > dino->p.x && (x < (dino->p.x + DINO_WIDTH)) && y > dino->p.y && (y < (dino->p.y + DINO_HEIGHT))) {
                return true;
            }
            // Bottom left
            x = enemy.p.x;
            y = enemy.p.y + enemy.size.height;
            if (x > dino->p.x && (x < (dino->p.x + DINO_WIDTH)) && y > dino->p.y && (y < (dino->p.y + DINO_HEIGHT))) {
                return true;
            }
            // Bottom right
            x = enemy.p.x + enemy.size.width;
            y = enemy.p.y + enemy.size.height;
            if (x > dino->p.x && (x < (dino->p.x + DINO_WIDTH)) && y > dino->p.y && (y < (dino->p.y + DINO_HEIGHT))) {
                return true;
            }
            // Top right
            x = enemy.p.x + enemy.size.width;
            y = enemy.p.y;
            if (x > dino->p.x && (x < (dino->p.x + DINO_WIDTH)) && y > dino->p.y && (y < (dino->p.y + DINO_HEIGHT))) {
                return true;
            }
        }
    }
    return false;
}


