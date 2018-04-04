#include "myLib.h"
#include "dino.h"

#include <stdbool.h>

int main(void) 
{
    REG_DISPCNT = MODE3 | BG2_ENABLE;
    Dino dino = (Dino) {(Point) {0, 0}, 0, false};
    running(&dino);
    return 0;
}

