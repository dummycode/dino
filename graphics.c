#include "myLib.h"
#include "graphics.h"
#include "colors.h"
#include "text.h"

volatile unsigned short *videoBuffer = (unsigned short *) 0x6000000;
unsigned int vBlankCounter = 0;

void waitForVblank()
{
    while (*SCANLINECOUNTER > 160);
    while (*SCANLINECOUNTER < 160);
    vBlankCounter++;
}

void drawRectangle(int row, int col, int width, int height, unsigned int color)
{
    for (int r = 0; r < height; r++) {
        DMA[3].src = &color;
        DMA[3].dst = &videoBuffer[OFFSET(row + r, col, SCREEN_WIDTH)];
        DMA[3].cnt = width | DMA_SOURCE_FIXED | DMA_ON;
    }
}

void drawImage(int row, int col, int width, int height, const unsigned short* image)
{
    for (int r = 0; r < height; r++) {
        DMA[3].src = &image[OFFSET(r, 0, width)];
        DMA[3].dst = &videoBuffer[OFFSET(row + r, col, SCREEN_WIDTH)];
        DMA[3].cnt = width | DMA_ON;
    }
}

void drawFullScreenImage(const unsigned short* image)
{
  DMA[3].src = image;
  DMA[3].dst = videoBuffer;
  DMA[3].cnt = SCREEN_WIDTH * SCREEN_HEIGHT | DMA_ON;
}

void setPixel(int row, int col, unsigned short color)
{
    videoBuffer[OFFSET(row, col, SCREEN_WIDTH)] = color;
}
