#ifndef COLORS_H
#define COLORS_H

#define COLOR(r,g,b) ((r) + ((g) << 5) + ((b) << 10))

// Vars
#define BACKGROUND_COLOR 0x7BDE
#define TEXT_COLOR 0x294A
#define BLACK   COLOR(0, 0, 0)


#define WHITE   COLOR(31, 31, 31)
#define RED     COLOR(31,0,0)
#define GREEN   COLOR(0, 31, 0)
#define BLUE    COLOR(0,0,31)
#define YELLOW  COLOR(31,31,0)
#define CYAN    COLOR(0,31,31)
#define MAGENTA COLOR(31,0,31)
#define GRAY    COLOR(25, 25, 25)

#endif
