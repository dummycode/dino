#include "myLib.h"
#include "graphics.h"
#include "colors.h"
#include "text.h"

volatile unsigned short *videoBuffer = (unsigned short *)0x6000000;

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

void drawImageSketchy(int row, int col, int width, int height, const unsigned short* image)
{
    for (int r = row; r < height; r++) {
        for (int c = col; c < width; c++) {
            if (r > 0 && c > 0 && r < SCREEN_HEIGHT - 1 && c < SCREEN_WIDTH - 1) {
                drawString(0, 0, "test test", TEXT_COLOR, BACKGROUND_COLOR);
                setPixel(r, c, image[OFFSET(r, 0, width)]);
            }
        }
    }
}

void setPixel(int row, int col, unsigned short color)
{
    videoBuffer[OFFSET(row, col, SCREEN_WIDTH)] = color;
}

void waitForVblank()
{
    while (*SCANLINECOUNTER > 160)
        ;
    while (*SCANLINECOUNTER < 160)
        ;
}
