#ifndef GRAPHICS_H
#define GRAPHICS_H

// Vars
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 160
#define DINO_HEIGHT 25
#define DINO_WIDTH 25

// MACROS
#define OFFSET(r, c, w) ((r) * (w) + (c))

unsigned int vBlankCounter = 0;

// Prototypes
void drawImage(int row, int col, int width, int height, const unsigned short* image);
void drawRectangle(int row, int col, int width, int height, unsigned int color);
void setPixel(int row, int col, unsigned short color);
void waitForVblank();

#endif
