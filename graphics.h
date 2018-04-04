#ifndef GRAPHICS_H
#define GRAPHICS_H

// Vars
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 160

// MACROS
#define OFFSET(r, c, w) ((r) * (w) + (c))

// Prototypes
void drawImage(int row, int col, int width, int height, const unsigned short* image);
void drawRectangle(int row, int col, int width, int height, unsigned int color); 
void waitForVblank();

#endif

